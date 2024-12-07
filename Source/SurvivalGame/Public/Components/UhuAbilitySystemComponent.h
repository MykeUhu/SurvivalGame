// UhuAbilitySystemComponent.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemComponent.h"
#include "UhuAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);
/**
 * UhuAbilitySystemComponent erweitert das Standard Ability System Component
 * und ermöglicht die Integration von Gameplay Ability System in unsere Charaktere.
 */
UCLASS()
class SURVIVALGAME_API UUhuAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UUhuAbilitySystemComponent();
	void AbilityActorInfoSet();
	FEffectAssetTags EffectAssetTags;

	// Ability starten
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void StartAbility(FGameplayTag AbilityTag);

	// Status aktualisieren
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void UpdateAbilityStatus(FGameplayTag AbilityTag, int32 Level);

	// Replikation für Abilities
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Diese Funktion wird bei Änderung des Ability-Status aufgerufen
	UFUNCTION(NetMulticast, Reliable)
	void MulticastUpdateAbilityStatus(FGameplayTag AbilityTag, int32 Level);

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
