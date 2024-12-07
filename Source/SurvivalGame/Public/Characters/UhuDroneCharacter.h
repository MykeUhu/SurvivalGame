// UhuDroneCharacter.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UhuGameplayTags.h"
#include "UhuDroneCharacter.generated.h"

UCLASS()
class SURVIVALGAME_API AUhuDroneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUhuDroneCharacter();

	// Verweise auf AbilitySystemComponent und Setup
	UPROPERTY(Replicated)
	class UUhuAbilitySystemComponent* AbilitySystemComponent;

protected:
	virtual void BeginPlay() override;

	// NetMulticast Funktion, um Emote auf allen Clients zu verarbeiten
	UFUNCTION(NetMulticast, Reliable)
	void MulticastHandleEmote(FGameplayTag EmoteTag);

	// Setup für die Replikation der Komponenten
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
