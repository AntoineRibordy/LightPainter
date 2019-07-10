// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "PaletteMenu.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaletteMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

protected:


	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	UButton* BackButton;
	
	UFUNCTION()
	void BackButtonClicked();

};
