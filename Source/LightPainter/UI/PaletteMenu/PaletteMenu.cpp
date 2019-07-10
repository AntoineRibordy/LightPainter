// Fill out your copyright notice in the Description page of Project Settings.

#include "PaletteMenu.h"
#include "LightPainterGameModeBase.h"
#include "PaintingGameMode.h"

bool UPaletteMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!BackButton) return false;
	BackButton->OnPressed.AddDynamic(this, &UPaletteMenu::BackButtonClicked);
	return true;
}

void UPaletteMenu::BackButtonClicked()
{
	auto GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->SaveAndQuit();
}