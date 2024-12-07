// UhuSurvivalCharacter.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/UhuSaveGameComponent.h"
#include "UhuGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Game/Interfaces/PlayerInterface.h"
#include "GameFramework/SpringArmComponent.h"
#include "UhuSurvivalCharacter.generated.h"

// Forward Declarations
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;
class UUhuEmoteWheelComponent;
class UUhuMovementComponent;
class UUhuCameraComponent;
class AUhuDroneCharacter;
class UUhuMovementDataAsset;

/**
 * AUhuSurvivalCharacter
 * Basis-Charakterklasse für den Spieler im Survival-Game.
 * Unterstützt das Gameplay Ability System, Emotes, und Spielstand-Speicherung.
 */
UCLASS(Abstract)
class SURVIVALGAME_API AUhuSurvivalCharacter : public ACharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:
	// Constructor
	AUhuSurvivalCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	/** Called when the character is possessed by a controller */
	virtual void PossessedBy(AController* NewController) override;

	/** Called when the PlayerState is replicated */
	virtual void OnRep_PlayerState() override;

	/** Returns the associated Ability System Component */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	/** Returns the AttributeSet instance */
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	/** IPlayerInterface Implementation: Returns the OnASCRegistered delegate */
	virtual FOnASCRegistered& GetOnASCRegisteredDelegate() override;

	/** Handles replication setup */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Event fired when the Ability System Component is registered */
	FOnASCRegistered OnAscRegistered;

	/** Set MovementSpeed Tag for Player */
	UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
	void SetMovementSpeedTag(FGameplayTag NewSpeedTag);

	/** Move of the Character */
	UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
	void CharacterMove(const FVector2D& MoveDirection);

	/** Adjust MovementSpeed */
	UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
	void AdjustMovementSpeed(int32 Delta);

	/** Restore old MovementSpeed */
	UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
	void RestorePreviousMovementSpeed();

	/** Get the Speed Tag */
	UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
	FGameplayTag GetCurrentSpeedTag() const { return CurrentSpeedTag; }

	/** Saves the character's progress */
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SaveProgress();

	/** Loads the character's progress */
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void LoadProgress();

	/** Returns the custom movement component */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	UUhuMovementComponent* GetUhuMovementComponent() const { return UhuMovementComponent; }

protected:
	/** Called when the game begins */
	virtual void BeginPlay() override;

	/** Initializes ability-related actor info */
	virtual void InitAbilityActorInfo();

	/** Applies a GameplayEffect to the character */
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	/** Initializes the character's default attributes */
	virtual void InitializeDefaultAttributes() const;

	/** Grants the character default abilities */
	void AddCharacterAbilities();

	/** Handles camera and spring arm components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;  // Der SpringArm, an dem die Kamera befestigt wird

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;  // Die Kamera-Komponente

	/**
	 * Sends an emote activation command to the associated drone.
	 * This function is executed on the server.
	 */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSendEmoteToDrone(FGameplayTag EmoteTag);

	/** Validates the ServerSendEmoteToDrone call */
	virtual bool ServerSendEmoteToDrone_Validate(FGameplayTag EmoteTag);

	/** Implements the ServerSendEmoteToDrone logic */
	virtual void ServerSendEmoteToDrone_Implementation(FGameplayTag EmoteTag);

	/** Initializes default attribute GameplayEffects */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	/** Custom movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UUhuMovementComponent> UhuMovementComponent;

	/** Movement data asset */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UUhuMovementDataAsset> MovementDataAsset;

	/** Function to change movement speed */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ChangeMovementSpeed(FGameplayTag SpeedTag);

	// ** Property for SpeedTag */
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FGameplayTag CurrentSpeedTag;

	
	UPROPERTY(ReplicatedUsing = OnRep_MovementSpeed)
	float MaxWalkSpeed;

	UFUNCTION()
	void OnRep_MovementSpeed();
private:
	/** Reference to the Ability System Component */
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	/** Reference to the Attribute Set */
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	/** Component for handling emotes */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UUhuEmoteWheelComponent* EmoteWheelComponent;

	/** Component for saving and loading progress */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UUhuSaveGameComponent* SaveGameComponent;

	/** Reference to the associated drone character */
	UPROPERTY(Replicated)
	AUhuDroneCharacter* AssociatedDrone;

	/** Movement belong things */
	int32 CurrentSpeedLevel;
	void ApplyMovementSpeed(float Speed);
	void RemoveAllMovementSpeedTags();
	void ApplyMovementSpeedTag(FGameplayTag SpeedTag);
	FGameplayTag PreviousSpeedTag;
};
