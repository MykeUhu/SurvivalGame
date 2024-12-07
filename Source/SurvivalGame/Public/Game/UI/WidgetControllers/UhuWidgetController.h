// UhuWidgetController.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UhuWidgetController.generated.h"

// Forward Declarations
class AUhuPlayerState;
class UUhuAttributeSet;
class AUhuPlayerController;
class UUhuAbilitySystemComponent;
class UAbilitySystemComponent;

/** 
 * Struktur zur Übergabe von Initialisierungsparametern für Widget-Controller.
 */
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	
	FWidgetControllerParams() {}

	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
		: PlayerController(PC),
		  PlayerState(PS),
		  AbilitySystemComponent(ASC),
		  AttributeSet(AS) {}

	/** Referenz auf den PlayerController. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	/** Referenz auf den PlayerState. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	/** Referenz auf die AbilitySystemComponent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	/** Referenz auf das AttributeSet. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * Basisklasse für Widget-Controller zur Verwaltung von UI-Logik und Bindung an Gameplay-Daten.
 */
UCLASS()
class SURVIVALGAME_API UUhuWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	/** Setzt die Initialisierungsparameter für den Widget-Controller. */
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	/** Überträgt initiale Werte an Widgets. */
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();

	/** Bindet Callbacks an Gameplay- oder Engine-Ereignisse. */
	virtual void BindCallbacksToDependencies();

protected:
	// -------------------------
	// Engine-Referenzen
	// -------------------------
	
	/** Referenz auf den PlayerController. */
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	/** Referenz auf den PlayerState. */
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	/** Referenz auf die AbilitySystemComponent. */
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	/** Referenz auf das AttributeSet. */
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	// -------------------------
	// Uhu-spezifische Referenzen
	// -------------------------

	/** Casted Referenz auf AUhuPlayerController. */
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<AUhuPlayerController> UhuPlayerController;

	/** Casted Referenz auf AUhuPlayerState. */
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<AUhuPlayerState> UhuPlayerState;

	/** Casted Referenz auf UUhuAbilitySystemComponent. */
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UUhuAbilitySystemComponent> UhuAbilitySystemComponent;

	/** Casted Referenz auf UUhuAttributeSet. */
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UUhuAttributeSet> UhuAttributeSet;

	// -------------------------
	// Hilfsfunktionen
	// -------------------------

	/** Gibt den UhuPlayerController zurück. */
	AUhuPlayerController* GetUhuPC();

	/** Gibt den UhuPlayerState zurück. */
	AUhuPlayerState* GetUhuPS();

	/** Gibt die UhuAbilitySystemComponent zurück. */
	UUhuAbilitySystemComponent* GetUhuASC();

	/** Gibt das UhuAttributeSet zurück. */
	UUhuAttributeSet* GetUhuAS();
};
