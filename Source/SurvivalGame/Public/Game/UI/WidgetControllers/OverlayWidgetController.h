// OverlayWidgetController.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "UhuWidgetController.h"
#include "OverlayWidgetController.generated.h"

// Vorwärtsdeklarationen
class UUhuUserWidget;
class UUhuAbilitySystemComponent;

// Delegat, um Änderungen an einem Attribut zu signalisieren
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

/**
 * OverlayWidgetController ist eine spezialisierte Klasse für die Steuerung von UI-Overlays
 * und die Bindung an Gameplay-Attribute, die durch das Gameplay Ability System (GAS) verwaltet werden.
 */
UCLASS(BlueprintType, Blueprintable)
class SURVIVALGAME_API UOverlayWidgetController : public UUhuWidgetController
{
	GENERATED_BODY()

public:
	// Überschreibt die Basisimplementierung, um initiale Werte an das Widget zu übertragen
	virtual void BroadcastInitialValues() override;

	// Überschreibt die Basisimplementierung, um Callbacks für Änderungen an Abhängigkeiten zu binden
	virtual void BindCallbacksToDependencies() override;
	
	// Delegat für die Signalisierung von Änderungen an der Gesundheit
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	// Delegat für die Signalisierung von Änderungen an der maximalen Gesundheit
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:
	/**
	 * Hilfsfunktion, um eine Zeile aus einer DataTable basierend auf einem Gameplay-Tag zu extrahieren.
	 * @tparam T - Der Typ der Zeile, die aus der DataTable abgerufen werden soll.
	 * @param DataTable - Die DataTable, aus der die Zeile abgerufen werden soll.
	 * @param Tag - Der Gameplay-Tag, der als Schlüssel dient.
	 * @return Zeiger auf die gefundene Zeile oder nullptr, falls keine Zeile gefunden wurde.
	 */
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

// Implementierung der templatebasierten Funktion
template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	// Sucht die Zeile anhand des Tags und gibt sie zurück (oder nullptr, falls nicht vorhanden).
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
