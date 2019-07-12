// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingPicker.h"

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
	
	Refresh();
}

void APaintingPicker::EnableDeleteMode()
{
	if (!GetPaintingGridWidget()) return;

	GetPaintingGridWidget()->ClearPaintings();
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

	Refresh();
}

void APaintingPicker::UpdateCurrentPage(int32 Offset)
{
	CurrentPage = FMath::Clamp(CurrentPage + Offset, 0, GetNumberOfPages() - 1);
	Refresh();
}

void APaintingPicker::RefreshSlots()
{
	if (!GetPaintingGridWidget()) return;

	GetPaintingGridWidget()->ClearPaintings();

	// From which slot we load cards, depending on which grid page we are currently
	int32 StartOffset = CurrentPage * GetPaintingGridWidget()->GetNumberofSlots();

	UPainterSaveGameIndex* Index = UPainterSaveGameIndex::Load();
	TArray<FString> SlotNames = Index->GetSlotNames();
	// List paintings with a startoffset which depends on which page of the painting grid we want to display
	for (int32 SlotIndex = 0; 
		(SlotIndex < GetPaintingGridWidget()->GetNumberofSlots()) && 
		SlotIndex + StartOffset < UPainterSaveGameIndex::Load()->GetSlotNames().Num();
		SlotIndex++)
	{
		GetPaintingGridWidget()->AddPainting(SlotIndex, SlotNames[SlotIndex + StartOffset]);
	}
}

void APaintingPicker::RefreshDots()
{
	if (!GetPaintingGridWidget()) return;
	GetPaintingGridWidget()->ClearPaginationDots();
	for (int Index = 0; Index < GetNumberOfPages(); Index++)
	{
		GetPaintingGridWidget()->AddPaginationDot(Index == CurrentPage);
	}

}

int32 APaintingPicker::GetNumberOfPages() const
{
	// Get number of slots in Painting Grid Widget
	if (!GetPaintingGridWidget()) return 0;
	int32 NumberOfSlotsPerPage = GetPaintingGridWidget()->GetNumberofSlots();
	// Get number of Saved Paintings
	int32 NumberOfSavedPaintings = UPainterSaveGameIndex::Load()->GetSlotNames().Num();

	// FMath divide up, turn integers into floating point division
	return FMath::CeilToInt((float) NumberOfSavedPaintings / NumberOfSlotsPerPage);
}

