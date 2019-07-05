// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGridCard.h"
#include "Kismet/GameplayStatics.h"

void UPaintingGridCard::SetPaintingName(FString PaintingName)
{
	SlotName->SetText(FText::FromString(PaintingName));

	CardButton->OnClicked.AddDynamic(this, &UPaintingGridCard::CardButtonClicked);
}

void UPaintingGridCard::CardButtonClicked()
{
	FString CardName = (SlotName->GetText().ToString());
	FName LevelName = FName(TEXT("Main"));

	//TODO: Refactor out magic string
	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true, "SlotName=" + CardName);
}
