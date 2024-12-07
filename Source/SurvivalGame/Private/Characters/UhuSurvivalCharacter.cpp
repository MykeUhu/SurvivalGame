// UhuSurvivalCharacter.cpp
// Copyright by MykeUhu

#include "Characters/UhuSurvivalCharacter.h"

#include "UhuGameplayTags.h"
#include "SurvivalGame/SurvivalGame.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/UhuAbilitySystemComponent.h"
#include "Components/UhuEmoteWheelComponent.h"
#include "Components/UhuMovementComponent.h"
#include "Components/UhuSaveGameComponent.h"
#include "Game/Data/UhuMovementDataAsset.h"
#include "Game/Player/UhuPlayerController.h"
#include "Game/Player/UhuPlayerState.h"
#include "Game/UI/HUD/UhuHUD.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"

// -------------------------
// Konstruktor & Initialisierung
// -------------------------

AUhuSurvivalCharacter::AUhuSurvivalCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UUhuMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    // SpringArm für die Kamera erstellen
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);  // Anhängen an die Root-Komponente

    // SpringArm konfigurieren
    CameraBoom->TargetArmLength = 300.0f;  // Abstand der Kamera vom Charakter
    CameraBoom->bUsePawnControlRotation = true;  // Kamera folgt der Controller-Rotation

    // Kamera erstellen und an den SpringArm anhängen
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(CameraBoom);  // Kamera wird am SpringArm angehängt

    // Konfiguration der Kamera für 3rd Person
    CameraComponent->bUsePawnControlRotation = false;  // Kamera folgt nicht direkt dem Pawn, sondern wird vom Controller gesteuert

    // Weitere Komponenten initialisieren
    EmoteWheelComponent = CreateDefaultSubobject<UUhuEmoteWheelComponent>(TEXT("EmoteWheelComponent"));
    SaveGameComponent = CreateDefaultSubobject<UUhuSaveGameComponent>(TEXT("SaveGameComponent"));

    bReplicates = true;
}


// -------------------------
// Game Start und Ability-System
// -------------------------


void AUhuSurvivalCharacter::BeginPlay()
{
    Super::BeginPlay();
    // Initialize movement data
    if (UhuMovementComponent && MovementDataAsset)
    {
        UhuMovementComponent->InitializeWithNewMovementDataAsset(MovementDataAsset);
    }
        if (MovementDataAsset && MovementDataAsset->DefaultSpeedTag.IsValid())
        {
            SetMovementSpeedTag(MovementDataAsset->DefaultSpeedTag);
        }
}

void AUhuSurvivalCharacter::ChangeMovementSpeed(FGameplayTag SpeedTag)
{
    if (UhuMovementComponent)
    {
        UhuMovementComponent->UpdateMovementSpeed(SpeedTag);
    }
}

void AUhuSurvivalCharacter::OnRep_MovementSpeed()
{
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
    }
}

void AUhuSurvivalCharacter::ApplyMovementSpeed(float Speed)
{
    if (HasAuthority())
    {
        MaxWalkSpeed = Speed;
        OnRep_MovementSpeed();
    }
}

void AUhuSurvivalCharacter::RemoveAllMovementSpeedTags()
{
    if (AbilitySystemComponent)
    {
        for (const FMovementSpeedLevel& SpeedLevel : MovementDataAsset->SpeedLevels)
        {
            AbilitySystemComponent->RemoveLooseGameplayTag(SpeedLevel.SpeedTag);
        }
    }
}

void AUhuSurvivalCharacter::ApplyMovementSpeedTag(FGameplayTag SpeedTag)
{
    if (AbilitySystemComponent)
    {
        if (CurrentSpeedTag != FUhuGameplayTags::Get().Movement_Speed_0)
        {
            PreviousSpeedTag = CurrentSpeedTag;
        }
        CurrentSpeedTag = SpeedTag;
        AbilitySystemComponent->AddLooseGameplayTag(SpeedTag);
    }
}

// -------------------------
// Controller- und PlayerState-Events
// -------------------------

void AUhuSurvivalCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    // Initialisiert das Ability-System auf dem Server
    InitAbilityActorInfo();
    AddCharacterAbilities();
}

void AUhuSurvivalCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    // Initialisiert das Ability-System auf Clients
    InitAbilityActorInfo();
}

// -------------------------
// Ability-System-Integration
// -------------------------

void AUhuSurvivalCharacter::InitAbilityActorInfo()
{
    AUhuPlayerState* UhuPlayerState = GetPlayerState<AUhuPlayerState>();
    check(UhuPlayerState);

    // Initialisiert das Ability-System
    UhuPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(UhuPlayerState, this);
    Cast<UUhuAbilitySystemComponent>(UhuPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

    AbilitySystemComponent = UhuPlayerState->GetAbilitySystemComponent();
    AttributeSet = UhuPlayerState->GetAttributeSet();
    OnAscRegistered.Broadcast(AbilitySystemComponent);

    // Initialisiert das HUD
    if (AUhuPlayerController* UhuPlayerController = Cast<AUhuPlayerController>(GetController()))
    {
        if (AUhuHUD* UhuHUD = Cast<AUhuHUD>(UhuPlayerController->GetHUD()))
        {
            UhuHUD->InitOverlay(UhuPlayerController, UhuPlayerState, AbilitySystemComponent, AttributeSet);
        }
    }

    // Standard-Attribute initialisieren
    InitializeDefaultAttributes();
}

UAbilitySystemComponent* AUhuSurvivalCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

FOnASCRegistered& AUhuSurvivalCharacter::GetOnASCRegisteredDelegate()
{
    return OnAscRegistered;
}

void AUhuSurvivalCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
    check(IsValid(GetAbilitySystemComponent()));
    check(GameplayEffectClass);
    FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
    ContextHandle.AddSourceObject(this);
    const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
    GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AUhuSurvivalCharacter::InitializeDefaultAttributes() const
{
    ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
    ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
    ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
}

void AUhuSurvivalCharacter::AddCharacterAbilities()
{
    UUhuAbilitySystemComponent* UhuASC = CastChecked<UUhuAbilitySystemComponent>(AbilitySystemComponent);
    if (!HasAuthority()) return;

    // Hier können Startfähigkeiten hinzugefügt werden
    // UhuASC->AddCharacterAbilities(StartupAbilities);
}

// -------------------------
// Fortschrittsverwaltung
// -------------------------

void AUhuSurvivalCharacter::SaveProgress()
{
    SaveGameComponent->SaveGameData();
}

void AUhuSurvivalCharacter::LoadProgress()
{
    SaveGameComponent->LoadGameData();
}

// -------------------------
// Emote-Interaktionen mit der Drohne
// -------------------------

void AUhuSurvivalCharacter::ServerSendEmoteToDrone_Implementation(FGameplayTag EmoteTag)
{
    // Logik für das Senden eines Emotes an die Drohne
    UE_LOG(LogTemp, Log, TEXT("Emote sent to drone: %s"), *EmoteTag.ToString());
}

bool AUhuSurvivalCharacter::ServerSendEmoteToDrone_Validate(FGameplayTag EmoteTag)
{
    // Füge hier Validierungslogik hinzu, falls erforderlich
    return true;
}

// -------------------------
// Replikation
// -------------------------

void AUhuSurvivalCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Repliziert die Drohne
    DOREPLIFETIME(AUhuSurvivalCharacter, AssociatedDrone);
}

void AUhuSurvivalCharacter::SetMovementSpeedTag(FGameplayTag NewSpeedTag)
{
    if (!MovementDataAsset || !NewSpeedTag.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Movement Data Asset or Speed Tag!"));
        return;
    }

    RemoveAllMovementSpeedTags();
    ApplyMovementSpeedTag(NewSpeedTag);

    const FMovementSpeedLevel SpeedLevel = MovementDataAsset->GetSpeedLevelForTag(NewSpeedTag);
    if (SpeedLevel.Speed >= 0.f)
    {
        ApplyMovementSpeed(SpeedLevel.Speed);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Speed Level for Tag: %s"), *NewSpeedTag.ToString());
    }
}

void AUhuSurvivalCharacter::CharacterMove(const FVector2D& MoveDirection)
{
    if (Controller)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MoveDirection.X);
        AddMovementInput(RightDirection, MoveDirection.Y);
    }
}

void AUhuSurvivalCharacter::AdjustMovementSpeed(int32 Delta)
{
    if (!MovementDataAsset) return;

    int32 CurrentIndex = MovementDataAsset->SpeedLevels.IndexOfByPredicate([this](const FMovementSpeedLevel& SpeedLevel) {
        return SpeedLevel.SpeedTag == CurrentSpeedTag;
    });

    if (CurrentIndex != INDEX_NONE)
    {
        int32 NewIndex = FMath::Clamp(CurrentIndex + Delta, 1, MovementDataAsset->SpeedLevels.Num() - 1);
        SetMovementSpeedTag(MovementDataAsset->SpeedLevels[NewIndex].SpeedTag);
    }
}

void AUhuSurvivalCharacter::RestorePreviousMovementSpeed()
{
    if (PreviousSpeedTag.IsValid())
    {
        SetMovementSpeedTag(PreviousSpeedTag);
    }
    else
    {
        SetMovementSpeedTag(FUhuGameplayTags::Get().Movement_Speed_1);
    }
}
