// UhuDroneCharacter.cpp
// Copyright by MykeUhu

#include "Characters/UhuDroneCharacter.h"
#include "Net/UnrealNetwork.h"

// Konstruktor
AUhuDroneCharacter::AUhuDroneCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true; // Multiplayer-fähig
}

// BeginPlay
void AUhuDroneCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// NetMulticast-Implementierung für das Emote
void AUhuDroneCharacter::MulticastHandleEmote_Implementation(FGameplayTag EmoteTag)
{
	// Hier implementierst du die Logik, wie die Drohne mit Emotes umgeht
	// Beispiel: Wenn die Drohne ein Emote empfängt, wird eine Animation abgespielt.
	UE_LOG(LogTemp, Warning, TEXT("Drohne empfängt Emote: %s"), *EmoteTag.ToString());
}

// Replication der Variablen
void AUhuDroneCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Hier könnten noch weitere Eigenschaften hinzugefügt werden, die repliziert werden müssen
}
