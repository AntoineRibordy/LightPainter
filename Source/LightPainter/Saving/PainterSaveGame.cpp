// Fill out your copyright notice in the Description page of Project Settings.

#include "PainterSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Stroke.h"
#include "EngineUtils.h"

void UPainterSaveGame::SerializeFromWorld(UWorld * World)
{
	// Clear array
	Strokes.Empty();
	// Iterate over all strokes
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		// TODO: Serialize
		Strokes.Add(StrokeItr->GetClass());
	}
}

void UPainterSaveGame::DeserializeToWorld(UWorld * World)
{
	ClearWorld(World);

	for (TSubclassOf<AStroke> StrokeClass : Strokes)
	{
		AStroke* NewStroke = World->SpawnActor<AStroke>(StrokeClass);
	}
}

UPainterSaveGame::UPainterSaveGame()
{
	PaintingName = TEXT("Drawing");
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
	USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(StaticClass());
	return Cast<UPainterSaveGame>(NewSaveGame);
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, PaintingName, 0);
}

UPainterSaveGame * UPainterSaveGame::Load()
{
	
	UPainterSaveGame* Painting = Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(UPainterSaveGame::StaticClass()));
	return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(Painting->PaintingName, 0));
}
