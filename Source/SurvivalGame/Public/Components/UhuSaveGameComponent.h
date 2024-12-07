// SaveGameComponent.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UhuSaveGameComponent.generated.h"

class UGameSave;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVALGAME_API UUhuSaveGameComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUhuSaveGameComponent();

	// Spielstand speichern
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SaveGameData();

	// Spielstand laden
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void LoadGameData();

private:
	// Methode, um den Spielstand in einer Datei zu speichern
	void SaveToSlot(UGameSave* SaveGameInstance);

	// Methode, um den Spielstand aus einer Datei zu laden
	UGameSave* LoadFromSlot();
};
