// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Saving/PainterSaveGame.h"

void APaintingGameMode::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	SlotName = UGameplayStatics::ParseOption(Options, "SlotName");
	UE_LOG(LogTemp, Warning, TEXT("Returned option: %s"), *SlotName);
}

void APaintingGameMode::SaveAndQuit()
{
	Save();

	FName LevelName = FName(TEXT("MainMenu"));
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void APaintingGameMode::Save()
{

	UPainterSaveGame* Painting = UPainterSaveGame::Load(SlotName);
	if (!Painting) return;
	Painting->SerializeFromWorld(GetWorld());
	Painting->Save();

	/*UPainterSaveGame* Painting = UPainterSaveGame::CreateGame();
	if (Painting && Painting->Save())
	{
		CurrentSlotName = Painting->GetSlotName();
	}*/
}

void APaintingGameMode::Load()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(SlotName);
	if (Painting)
	{
		Painting->DeserializeToWorld(GetWorld());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No save slot present %s"), *SlotName);
	}
}

void APaintingGameMode::BeginPlay()
{
	Super::BeginPlay();
	Load();
}
