// GameSave.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSave.generated.h"

UCLASS()
class SURVIVALGAME_API UGameSave : public USaveGame
{
	GENERATED_BODY()

public:
	// Spielerposition speichern
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveData")
	FVector PlayerPosition;

	// Beispiel für Inventardaten oder andere Speicherwerte
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveData")
	TArray<FString> PlayerInventory;
    
	// Weitere Werte wie Level, Punktestand, etc.
};
