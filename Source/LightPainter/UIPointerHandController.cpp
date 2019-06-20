// Fill out your copyright notice in the Description page of Project Settings.

#include "UIPointerHandController.h"
#include "InputCoreTypes.h"

AUIPointerHandController::AUIPointerHandController()
{
	InteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("InteractionComponent"));
	InteractionComponent->SetupAttachment(MotionController);

	InteractionComponent->bShowDebug = true;

}

void AUIPointerHandController::TriggerPressed()
{
	InteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
}

void AUIPointerHandController::TriggerReleased()
{
	InteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
}


