// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingPicker.h"
#include "PaintingGrid.h"
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

// Called when the game starts or when spawned
void APaintingPicker::BeginPlay()
{
	Super::BeginPlay();
	UPainterSaveGameIndex* Index = UPainterSaveGameIndex::Load();
	TArray<FString> SlotNames = Index->GetSlotNames();
	// List all the paintings and add them to the grid
	UPaintingGrid* PaintingGridWidget = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (!PaintingGridWidget) return;
	for (int SlotIndex = 0; SlotIndex < SlotNames.Num(); SlotIndex++)
	{
		PaintingGridWidget->AddPainting(SlotIndex, SlotNames[SlotIndex]);
	}  
}

