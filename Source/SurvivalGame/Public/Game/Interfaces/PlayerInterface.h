#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "PlayerInterface.generated.h"

class UAbilitySystemComponent;


DECLARE_MULTICAST_DELEGATE_OneParam(FOnASCRegistered, UAbilitySystemComponent*)

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

class SURVIVALGAME_API IPlayerInterface
{
	GENERATED_BODY()

public:
	virtual FOnASCRegistered& GetOnASCRegisteredDelegate() = 0;
};