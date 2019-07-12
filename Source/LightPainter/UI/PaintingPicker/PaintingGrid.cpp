// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGrid.h"
#include "Components/HorizontalBoxSlot.h"
#include "Layout/Margin.h"
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

void UPaintingGrid::ClearPaginationDots()
{
	if (!PaginationDots) return;
	PaginationDots->ClearChildren();
}

void UPaintingGrid::AddPaginationDot(bool Active)
{
	if (!PaginationDots) return;
	UPaginationDot* NewDot = CreateWidget<UPaginationDot>(GetWorld(), PaginationDotClass);
	if (!NewDot) return;
	NewDot->SetActive(Active);

	UHorizontalBoxSlot* Slot = PaginationDots->AddChildToHorizontalBox(NewDot);
	Slot->SetPadding(FMargin(PaginationMargin, 0));
}

int32 UPaintingGrid::GetNumberofSlots() const
{
	return PaintingGrid->GetChildrenCount();
}
