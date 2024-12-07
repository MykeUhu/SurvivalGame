#include "Characters/UhuSurvivalCharacter.h"

#include "UhuGameplayTags.h"
#include "SurvivalGame/SurvivalGame.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/UhuAbilitySystemComponent.h"
#include "Components/UhuEmoteWheelComponent.h"
#include "Components/UhuSaveGameComponent.h"
#include "Game/Player/UhuPlayerController.h"
#include "Game/Player/UhuPlayerState.h"
#include "Game/UI/HUD/UhuHUD.h"
#include "Net/UnrealNetwork.h"

// -------------------------
// Konstruktor & Initialisierung
// -------------------------

AUhuSurvivalCharacter::AUhuSurvivalCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Initialisierung der Komponenten
    EmoteWheelComponent = CreateDefaultSubobject<UUhuEmoteWheelComponent>(TEXT("EmoteWheelComponent"));
    SaveGameComponent = CreateDefaultSubobject<UUhuSaveGameComponent>(TEXT("SaveGameComponent"));

    bReplicates = true; // Aktiviert die Replikation für Multiplayer
}

void AUhuSurvivalCharacter::BeginPlay()
{
    Super::BeginPlay();
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
