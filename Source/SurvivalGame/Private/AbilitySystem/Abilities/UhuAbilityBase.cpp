#include "AbilitySystem/Abilities/UhuAbilityBase.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"

UUhuAbilityBase::UUhuAbilityBase()
{
	// Standardkonstruktor für benutzerdefinierte Abilities
}

void UUhuAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// Hier wird die Fähigkeit aktiviert
	UE_LOG(LogTemp, Log, TEXT("Ability Activated"));

	// Beispiel: Setze einen Status oder trigger eine andere Funktion
}

void UUhuAbilityBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Hier wird die Fähigkeit beendet
	UE_LOG(LogTemp, Log, TEXT("Ability Ended"));

	// Beispiel: Ressourcen zurücksetzen oder andere Logik durchführen
}
