#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "UhuPlayerController.generated.h"

// Forward-Declarations
class UInputAction;
class UInputMappingContext;
class UUhuAbilitySystemComponent;

/**
 * AUhuPlayerController
 * 
 * Der PlayerController für den SurvivalGame-Charakter, der Eingabe, Maus-Cursor 
 * und Gameplay-Mechaniken wie das Ability System integriert.
 */
UCLASS()
class SURVIVALGAME_API AUhuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Konstruktor
	AUhuPlayerController();

	/**
	 * Wird jeden Frame für den PlayerController aufgerufen.
	 * 
	 * @param DeltaTime Zeit, die seit dem letzten Frame vergangen ist.
	 */
	virtual void PlayerTick(float DeltaTime) override;

protected:
	/**
	 * Wird beim Start des Spiels für den PlayerController aufgerufen.
	 * Initialisiert Eingabesystem und Cursor-Modus.
	 */
	virtual void BeginPlay() override;

private:
	// -------------------------
	// Eigenschaften
	// -------------------------

	/** Der Eingabekontext für den Controller (Enhanced Input). */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> UhuContext;

	/** Zeiger auf die AbilitySystem-Komponente des kontrollierten Charakters. */
	UPROPERTY()
	TObjectPtr<UUhuAbilitySystemComponent> UhuAbilitySystemComponent;

	// -------------------------
	// Methoden
	// -------------------------

	/**
	 * Gibt die Ability System-Komponente des kontrollierten Charakters zurück.
	 * Falls sie noch nicht gesetzt ist, wird sie initialisiert.
	 * 
	 * @return Zeiger auf die UUhuAbilitySystemComponent.
	 */
	UUhuAbilitySystemComponent* GetASC();
};
