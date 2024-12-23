﻿// UhuPlayerController.cpp
// Copyright by MykeUhu

#include "Game/Player/UhuPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "UhuGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Characters/UhuSurvivalCharacter.h"
#include "Components/UhuAbilitySystemComponent.h"

// -------------------------
// Konstruktor & Initialisierung
// -------------------------

AUhuPlayerController::AUhuPlayerController()
{
	bReplicates = true; // Ermöglicht Replikation für Multiplayer
}

void AUhuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(UhuContext);

	// Enhanced Input-System konfigurieren
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(UhuContext, 0);
	}

	// Maus- und Eingabe-Modus konfigurieren
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AUhuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//EnhancedInputComponent->BindAction(SpeedAdjustAction, ETriggerEvent::Triggered, this, &AUhuPlayerController::AdjustSpeedWithMouseWheel);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUhuPlayerController::Move);
	}
}

// -------------------------
// Gameplay-Tick
// -------------------------

void AUhuPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// Zusätzliche Tick-Logik kann hier hinzugefügt werden
}

// -------------------------
// Ability-System-Integration
// -------------------------

UUhuAbilitySystemComponent* AUhuPlayerController::GetASC()
{
	if (UhuAbilitySystemComponent == nullptr)
	{
		// Sucht die Ability-System-Komponente des kontrollierten Pawns
		UhuAbilitySystemComponent = Cast<UUhuAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>())
		);
	}
	return UhuAbilitySystemComponent;
}

void AUhuPlayerController::Move(const FInputActionValue& InputValue)
{
	FVector2D MoveDirection = InputValue.Get<FVector2D>();

	if (AUhuSurvivalCharacter* ControlledCharacter = Cast<AUhuSurvivalCharacter>(GetPawn()))
	{
		// If the character is idle, restore the previous movement speed
		if (ControlledCharacter->GetCurrentSpeedTag().MatchesTag(FUhuGameplayTags::Get().Movement_Speed_0))
		{
			ControlledCharacter->RestorePreviousMovementSpeed();
		}

		ControlledCharacter->CharacterMove(MoveDirection);
	}
}

