// Fill out your copyright notice in the Description page of Project Settings.

#include "PainterSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Stroke.h"
#include "EngineUtils.h"

#include "Misc/Guid.h"


void UPainterSaveGame::SerializeFromWorld(UWorld * World)
{
	// Clear array
	Strokes.Empty();
	// Iterate over all strokes
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		// TODO: Serialize
		Strokes.Add(StrokeItr->SerializeToStruct());
	}
}

void UPainterSaveGame::DeserializeToWorld(UWorld * World)
{
	ClearWorld(World);

	for (FStrokeState StrokeStates : Strokes)
	{
		AStroke::SpawnAndDeserializeFromStruct(World, StrokeStates);
	}
}

void UPainterSaveGame::ClearWorld(UWorld * World)
{
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		StrokeItr->Destroy();
	}
}



UPainterSaveGame* UPainterSaveGame::CreateGame()
{
	
	UPainterSaveGame* NewSaveGame = Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
	NewSaveGame->SlotName = FGuid::NewGuid().ToString();
	return NewSaveGame;
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

UPainterSaveGame * UPainterSaveGame::Load(FString SlotName)
{
	
	return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
}

