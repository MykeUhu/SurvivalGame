// UhuMovementComponent.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTagContainer.h"
#include "UhuMovementComponent.generated.h"

class UUhuMovementDataAsset;

/**
 * UhuMovementComponent
 * 
 * Custom movement component for the Uhu Survival Game.
 * Handles character movement using data-driven speed levels.
 */
UCLASS()
class SURVIVALGAME_API UUhuMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UUhuMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Function to update movement speed based on the current speed tag
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void UpdateMovementSpeed(FGameplayTag SpeedTag);

	// Function to get the current speed tag
	UFUNCTION(BlueprintCallable, Category = "Movement")
	FGameplayTag GetCurrentSpeedTag() const { return CurrentSpeedTag; }

	// Function to initialize the movement component with the data asset
	void InitializeWithNewMovementDataAsset(const UUhuMovementDataAsset* NewMovementDataAsset);
	void InitializeDefaultMovementData();

protected:
	// Reference to the movement data asset
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UUhuMovementDataAsset> MovementDataAsset;

	// Current speed tag
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FGameplayTag CurrentSpeedTag;

};