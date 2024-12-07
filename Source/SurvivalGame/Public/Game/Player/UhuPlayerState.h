// UhuPlayerState.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "UhuPlayerState.generated.h"

// Forward declarations
class UAbilitySystemComponent;
class UAttributeSet;

// Delegate für Änderungen des Spieler-Stat-Werts (Level)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*StatValue*/)

UCLASS()
class SURVIVALGAME_API AUhuPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Konstruktor der PlayerState-Klasse
	AUhuPlayerState();

	// Delegate, das ausgelöst wird, wenn sich das Level des Spielers ändert
	FOnPlayerStatChanged OnLevelChangedDelegate;

	// Getter für das Level des Spielers
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }

	// Funktion, die die Replikationseigenschaften für das Level hinzufügt
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Implementierung der Fähigkeitsschnittstelle - Gibt den AbilitySystemComponent zurück
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Getter für das Attribut-Set des Spielers
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	// Funktion, die das Level des Spielers erhöht
	void AddToLevel(int32 InLevel);

protected:
	// Der AbilitySystemComponent des Spielers (sichtbar im Editor)
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	// Das Attribut-Set des Spielers (intern, keine Exposition im Editor)
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	// Das Level des Spielers (wird repliziert und über die OnRep_Level Funktion verarbeitet)
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;

	// Funktion, die bei einer Änderung des Levels aufgerufen wird
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
};
