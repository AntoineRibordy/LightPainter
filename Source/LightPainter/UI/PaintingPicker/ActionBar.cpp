// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionBar.h"

bool UActionBar::Initialize()
{
	if (!Super::Initialize()) return false;
	if (!DeleteButton) return false;
	DeleteButton->OnClicked.AddDynamic(this, &UActionBar::DeleteButtonClicked);
	if (!AddButton) return false;
	AddButton->OnClicked.AddDynamic(this, &UActionBar::AddButtonClicked);
	return true;
}

void UActionBar::DeleteButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Delete button clicked"));
}

void UActionBar::AddButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Add button clicked"));
}
