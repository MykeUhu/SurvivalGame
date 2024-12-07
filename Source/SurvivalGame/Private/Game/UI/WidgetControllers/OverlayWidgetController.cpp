#include "Game/UI/WidgetControllers/OverlayWidgetController.h"
#include "AbilitySystem/Attributes/UhuAttributeSet.h"

/** 
 * Überträgt die initialen Werte für die Gesundheit und maximale Gesundheit 
 * an die gebundenen Widgets.
 */
void UOverlayWidgetController::BroadcastInitialValues()
{
	// Sende den aktuellen Gesundheitswert an gebundene Widgets.
	OnHealthChanged.Broadcast(GetUhuAS()->GetHealth());

	// Sende den aktuellen Maximalwert der Gesundheit an gebundene Widgets.
	OnMaxHealthChanged.Broadcast(GetUhuAS()->GetMaxHealth());
}

/** 
 * Bindet Callbacks an Änderungen von Attributen in der AbilitySystemComponent.
 */
void UOverlayWidgetController::BindCallbacksToDependencies()
{
	// Bindet einen Lambda-Callback an Änderungen des Gesundheits-Attributs.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetUhuAS()->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			// Überträgt die neuen Gesundheitswerte.
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	// Bindet einen Lambda-Callback an Änderungen des Maximalwerts für Gesundheit.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetUhuAS()->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			// Überträgt die neuen Maximalwerte für Gesundheit.
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
}
