// UhuAbilityBase.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "UhuAbilityBase.generated.h"

/**
 * Basis-Klasse für alle benutzerdefinierten Abilities in unserem Spiel.
 * Diese Klasse kann für verschiedene Arten von Abilities erweitert werden.
 */
UCLASS()
class SURVIVALGAME_API UUhuAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UUhuAbilityBase();

	// Diese Methode wird aufgerufen, wenn die Fähigkeit aktiviert wird
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	// Diese Methode kann verwendet werden, um die Fähigkeit zu beenden
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	// Deine benutzerdefinierte Logik für die Fähigkeit könnte hier definiert werden
};
