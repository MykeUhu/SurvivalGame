// UhuMovementComponent.cpp
// Copyright by MykeUhu

#include "Components/UhuMovementComponent.h"
#include "Game/Data/UhuMovementDataAsset.h"

UUhuMovementComponent::UUhuMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UUhuMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializeDefaultMovementData();
}

void UUhuMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Add any per-frame update logic here
}

void UUhuMovementComponent::UpdateMovementSpeed(FGameplayTag SpeedTag)
{
	if (MovementDataAsset)
	{
		FMovementSpeedLevel SpeedLevel = MovementDataAsset->GetSpeedLevelForTag(SpeedTag);
		MaxWalkSpeed = SpeedLevel.Speed;
		CurrentSpeedTag = SpeedTag;
		// You might want to handle stamina cost here or in the character class
	}
}

void UUhuMovementComponent::InitializeWithNewMovementDataAsset(const UUhuMovementDataAsset* NewMovementDataAsset)
{
	if (NewMovementDataAsset)
	{
		UpdateMovementSpeed(NewMovementDataAsset->DefaultSpeedTag);
	}
}

void UUhuMovementComponent::InitializeDefaultMovementData()
{
	if (MovementDataAsset)
	{
		UpdateMovementSpeed(MovementDataAsset->DefaultSpeedTag);
	}
}

