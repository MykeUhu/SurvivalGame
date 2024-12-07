#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/UhuSaveGameComponent.h"
#include "UhuGameplayTags.h"
#include "Game/Interfaces/PlayerInterface.h"
#include "UhuSurvivalCharacter.generated.h"

// Forward Declarations
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;
class UUhuEmoteWheelComponent;
class AUhuDroneCharacter;

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
	AUhuSurvivalCharacter();

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

	/** Saves the character's progress */
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SaveProgress();

	/** Loads the character's progress */
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void LoadProgress();

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
};
