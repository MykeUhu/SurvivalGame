// UhuPlayerState.cpp
// Copyright by MykeUhu

#include "Game/Player/UhuPlayerState.h"

#include "AbilitySystem/Attributes/UhuAttributeSet.h"
#include "Components/UhuAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

AUhuPlayerState::AUhuPlayerState()
{
	// Initialisierung des Ability System Components (ASC)
	AbilitySystemComponent = CreateDefaultSubobject<UUhuAbilitySystemComponent>("AbilitySystemComponent");
	// Setzt den Ability System Component als replizierbar im Netzwerk
	AbilitySystemComponent->SetIsReplicated(true);
	// Definiert den Replikationsmodus für Gameplay Effects (Mixed = Mix aus sofortiger und verzögerter Replikation)
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Initialisierung des Attribut-Sets
	AttributeSet = CreateDefaultSubobject<UUhuAttributeSet>("AttributeSet");
}

void AUhuPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	// Ruft die Replikationseigenschaften der Elternklasse auf (in diesem Fall APlayerState)
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Repliziert das Level des Spielers
	DOREPLIFETIME(AUhuPlayerState, Level);
}

UAbilitySystemComponent* AUhuPlayerState::GetAbilitySystemComponent() const
{
	// Gibt den Ability System Component des Spielers zurück
	return AbilitySystemComponent;
}

void AUhuPlayerState::AddToLevel(int32 InLevel)
{
	// Erhöht das Level des Spielers um den angegebenen Wert
	Level += InLevel;
	// Benachrichtigt alle Abonnenten (wie UI oder andere Systeme) über die Leveländerung
	OnLevelChangedDelegate.Broadcast(Level);
}

void AUhuPlayerState::OnRep_Level(int32 OldLevel)
{
	// Wird aufgerufen, wenn das Level im Netzwerk repliziert wird und gibt die Leveländerung bekannt
	OnLevelChangedDelegate.Broadcast(Level);
}
