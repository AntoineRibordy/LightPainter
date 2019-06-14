// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PainterSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPainterSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	static UPainterSaveGame* CreateGame();
	bool Save();
	static UPainterSaveGame* Load();

	void SetState(FString NewState) { State = NewState; }
	FString GetState() const { return State; }

	void SerializeFromWorld(UWorld* World);
	void DeserializeToWorld(UWorld* World);

	UPainterSaveGame();

private:
	void ClearWorld(UWorld* World);

	// State
	UPROPERTY(VisibleAnywhere)
	FString PaintingName;

	UPROPERTY()
	FString State;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<class AStroke>> Strokes;
};
