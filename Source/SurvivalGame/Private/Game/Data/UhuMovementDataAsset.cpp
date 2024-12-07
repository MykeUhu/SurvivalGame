// UhuMovementDataAsset.cpp
// Copyright by MykeUhu

#include "Game/Data/UhuMovementDataAsset.h"

FMovementSpeedLevel UUhuMovementDataAsset::GetSpeedLevelForTag(FGameplayTag SpeedTag) const
{
	for (const FMovementSpeedLevel& SpeedLevel : SpeedLevels)
	{
		if (SpeedLevel.SpeedTag == SpeedTag)
		{
			return SpeedLevel;
		}
	}

	// If no matching tag is found, return a default speed level
	return FMovementSpeedLevel();
}
