// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGrid.h"
#include "Components/SizeBox.h"

void UPaintingGrid::AddPainting(int32 PaintingIndex, FString PaintingName)
{
	if (!PaintingGrid) return;

	UPaintingGridCard* NewWidget = CreateWidget<UPaintingGridCard>(GetWorld(), GridCardClass);
	if (!NewWidget) return;

	NewWidget->SetPaintingName(PaintingName);

	USizeBox* Child = Cast<USizeBox>(PaintingGrid->GetChildAt(PaintingIndex));
	if (!Child) return;
	Child->AddChild(NewWidget);
}

void UPaintingGrid::ClearPaintings()
{
	if (!PaintingGrid) return;
	for (int Index = 0; Index < PaintingGrid->GetChildrenCount(); Index++)
	{
		USizeBox* CardContainer = Cast<USizeBox>(PaintingGrid->GetChildAt(Index));
		if (!CardContainer) continue;
		CardContainer->ClearChildren();
	}
}
