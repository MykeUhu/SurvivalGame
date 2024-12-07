#include "Components/UhuEmoteWheelComponent.h"
#include "Net/UnrealNetwork.h"

// Konstruktor
UUhuEmoteWheelComponent::UUhuEmoteWheelComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Emote aktivieren
void UUhuEmoteWheelComponent::ActivateEmote(FGameplayTag EmoteTag)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		// Server-seitige Logik für das Aktivieren von Emotes
		UE_LOG(LogTemp, Warning, TEXT("Emote aktivieren auf dem Server: %s"), *EmoteTag.ToString());
	}
	else
	{
		// Aufruf des Servers, um das Emote zu aktivieren
		ServerActivateEmote(EmoteTag);
	}
}

// Server-Implementierung für das Aktivieren eines Emotes
void UUhuEmoteWheelComponent::ServerActivateEmote_Implementation(FGameplayTag EmoteTag)
{
	ActivateEmote(EmoteTag);
}

// Validierung des Serveraufrufs
bool UUhuEmoteWheelComponent::ServerActivateEmote_Validate(FGameplayTag EmoteTag)
{
	return true; // Hier kann eine Validierung hinzugefügt werden, wenn nötig
}

// Implementierung der GetLifetimeReplicatedProps Funktion
void UUhuEmoteWheelComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Hier könnten weitere Variablen repliziert werden, wenn notwendig
}
