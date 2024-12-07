#include "Game/UI/WidgetControllers/UhuWidgetController.h"

#include "AbilitySystem/Attributes/UhuAttributeSet.h"
#include "Components/UhuAbilitySystemComponent.h"
#include "Game/Player/UhuPlayerController.h"
#include "Game/Player/UhuPlayerState.h"

// -------------------------
// Initialisierung
// -------------------------

/** Setzt die Parameter des Widget-Controllers. */
void UUhuWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
    PlayerController = WCParams.PlayerController;
    PlayerState = WCParams.PlayerState;
    AbilitySystemComponent = WCParams.AbilitySystemComponent;
    AttributeSet = WCParams.AttributeSet;
}

/** Sendet initiale Werte an Widgets. */
void UUhuWidgetController::BroadcastInitialValues()
{
    // Logik zur Übertragung initialer Werte implementieren (z. B. Health, Mana, etc.).
}

/** Bindet Callbacks an Abhängigkeiten. */
void UUhuWidgetController::BindCallbacksToDependencies()
{
    // Logik zur Bindung von Callbacks an relevante Events implementieren.
}

// -------------------------
// Getter-Funktionen
// -------------------------

/** Gibt den `AUhuPlayerController` zurück, falls er gecastet werden kann. */
AUhuPlayerController* UUhuWidgetController::GetUhuPC()
{
    if (UhuPlayerController == nullptr)
    {
        UhuPlayerController = Cast<AUhuPlayerController>(PlayerController);
    }
    return UhuPlayerController;
}

/** Gibt den `AUhuPlayerState` zurück, falls er gecastet werden kann. */
AUhuPlayerState* UUhuWidgetController::GetUhuPS()
{
    if (UhuPlayerState == nullptr)
    {
        UhuPlayerState = Cast<AUhuPlayerState>(PlayerState);
    }
    return UhuPlayerState;
}

/** Gibt die `UUhuAbilitySystemComponent` zurück, falls sie gecastet werden kann. */
UUhuAbilitySystemComponent* UUhuWidgetController::GetUhuASC()
{
    if (UhuAbilitySystemComponent == nullptr)
    {
        UhuAbilitySystemComponent = Cast<UUhuAbilitySystemComponent>(AbilitySystemComponent);
    }
    return UhuAbilitySystemComponent;
}

/** Gibt das `UUhuAttributeSet` zurück, falls es gecastet werden kann. */
UUhuAttributeSet* UUhuWidgetController::GetUhuAS()
{
    if (UhuAttributeSet == nullptr)
    {
        UhuAttributeSet = Cast<UUhuAttributeSet>(AttributeSet);
    }
    return UhuAttributeSet;
}
