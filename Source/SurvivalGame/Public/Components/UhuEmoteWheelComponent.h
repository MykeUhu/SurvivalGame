// UhuEmoteWheelComponent.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UhuGameplayTags.h"
#include "UhuEmoteWheelComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVALGAME_API UUhuEmoteWheelComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUhuEmoteWheelComponent();

	UFUNCTION(BlueprintCallable, Category = "Emote")
	void ActivateEmote(FGameplayTag EmoteTag);

protected:
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerActivateEmote(FGameplayTag EmoteTag);

	// Deklariere hier die GetLifetimeReplicatedProps Funktion
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
