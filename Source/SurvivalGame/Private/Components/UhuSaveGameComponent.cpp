#include "Components/UhuSaveGameComponent.h"

#include "Game/SaveData/GameSave.h"
#include "Kismet/GameplayStatics.h"

// Konstruktor
UUhuSaveGameComponent::UUhuSaveGameComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Spielstand speichern
void UUhuSaveGameComponent::SaveGameData()
{
	UGameSave* SaveGameInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));

	// Spielerposition speichern
	SaveGameInstance->PlayerPosition = GetOwner()->GetActorLocation();

	// Beispiel für Inventardaten
	SaveGameInstance->PlayerInventory.Add(TEXT("Example Item"));

	// Spielstand speichern
	SaveToSlot(SaveGameInstance);
}

// Spielstand laden
void UUhuSaveGameComponent::LoadGameData()
{
	UGameSave* LoadedGame = LoadFromSlot();
	if (LoadedGame)
	{
		// Position laden
		GetOwner()->SetActorLocation(LoadedGame->PlayerPosition);

		// Inventardaten laden
		for (const FString& Item : LoadedGame->PlayerInventory)
		{
			// Beispiel: Debugging-Ausgabe der Items
			UE_LOG(LogTemp, Warning, TEXT("Loaded Item: %s"), *Item);
		}
	}
}

// Speichern des Spielstands in einer Datei
void UUhuSaveGameComponent::SaveToSlot(UGameSave* SaveGameInstance)
{
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("PlayerSaveSlot"), 0);
}

// Laden des Spielstands aus einer Datei
UGameSave* UUhuSaveGameComponent::LoadFromSlot()
{
	return Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSaveSlot"), 0));
}
