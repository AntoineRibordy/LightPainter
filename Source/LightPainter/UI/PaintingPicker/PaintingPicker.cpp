// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingPicker.h"
#include "PaintingGrid.h"
#include "ActionBar.h"
#include "PaintingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Saving/PainterSaveGame.h"
#include "Saving/PainterSaveGameIndex.h"

// Sets default values
APaintingPicker::APaintingPicker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	PaintingGrid = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaintingGrid"));
	PaintingGrid->SetupAttachment(Root);
	ActionBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionBar"));
	ActionBar->SetupAttachment(Root);
}

void APaintingPicker::AddPainting()
{
	UPainterSaveGame::CreateGame();
	
	RefreshSlots();
}

void APaintingPicker::EnableDeleteMode()
{
	UPaintingGrid* PaintingGridWidget = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (!PaintingGridWidget) return;

	PaintingGridWidget->ClearPaintings();
}

// Called when the game starts or when spawned
void APaintingPicker::BeginPlay()
{
	Super::BeginPlay();
	UActionBar* ActionBarWidget = Cast<UActionBar>(ActionBar->GetUserWidgetObject());
	if (ActionBarWidget) 
	{
		ActionBarWidget->SetParentPicker(this);
	}

	RefreshSlots();
}

void APaintingPicker::RefreshSlots()
{
	UPaintingGrid* PaintingGridWidget = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (!PaintingGridWidget) return;

	PaintingGridWidget->ClearPaintings();

	UPainterSaveGameIndex* Index = UPainterSaveGameIndex::Load();
	TArray<FString> SlotNames = Index->GetSlotNames();
	// List all the paintings and add them to the grid
	for (int SlotIndex = 0; SlotIndex < SlotNames.Num(); SlotIndex++)
	{
		PaintingGridWidget->AddPainting(SlotIndex, SlotNames[SlotIndex]);
	}
}

