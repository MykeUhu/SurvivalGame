#include "Components/UhuAbilitySystemComponent.h"

#include "Net/UnrealNetwork.h"

UUhuAbilitySystemComponent::UUhuAbilitySystemComponent()
{
	// Komponenteninitialisierung
	PrimaryComponentTick.bCanEverTick = true;
}

// Ability starten
void UUhuAbilitySystemComponent::StartAbility(FGameplayTag AbilityTag)
{
	// Überprüfen, ob die Fähigkeit existiert, und dann starten
	if (AbilityTag.IsValid())
	{
		// Hier kann das Starten der Fähigkeit mit einem Gameplay Ability Tag erfolgen
		// Beispiel: Fähigkeit aktivieren
		// Add your logic to activate the ability based on the tag
		UE_LOG(LogTemp, Log, TEXT("Ability started with tag: %s"), *AbilityTag.ToString());
	}
}

// Status einer Ability aktualisieren
void UUhuAbilitySystemComponent::UpdateAbilityStatus(FGameplayTag AbilityTag, int32 Level)
{
	if (AbilityTag.IsValid())
	{
		// Multicast aufrufen, um alle Clients zu benachrichtigen
		MulticastUpdateAbilityStatus(AbilityTag, Level);
	}
}

// Multicast-Funktion für Ability-Status-Änderung
void UUhuAbilitySystemComponent::MulticastUpdateAbilityStatus_Implementation(FGameplayTag AbilityTag, int32 Level)
{
	// Logik zur Aktualisierung des Ability-Status
	// Dies könnte z.B. das Setzen von neuen Statuswerten oder das Triggern von Animationen sein
	UE_LOG(LogTemp, Log, TEXT("Ability Status Updated: %s, Level: %d"), *AbilityTag.ToString(), Level);
}

// Replikation der Abilities
void UUhuAbilitySystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Hier können wir weitere Variablen hinzufügen, die repliziert werden sollen, z.B. ein Array von Abilities
	// Beispiel: OutLifetimeProps.Add(...);
}

void UUhuAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}

void UUhuAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UUhuAbilitySystemComponent::ClientEffectApplied);
	
}
