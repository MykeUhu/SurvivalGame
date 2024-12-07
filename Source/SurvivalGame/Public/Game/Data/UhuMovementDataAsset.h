﻿// UhuMovementDataAsset.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "UhuMovementDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FMovementSpeedLevel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StaminaCost = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag SpeedTag;
};

UCLASS()
class SURVIVALGAME_API UUhuMovementDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	TArray<FMovementSpeedLevel> SpeedLevels;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FMovementSpeedLevel GetSpeedLevelForTag(FGameplayTag SpeedTag) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	FGameplayTag DefaultSpeedTag;
};