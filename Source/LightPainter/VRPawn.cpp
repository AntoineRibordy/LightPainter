// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Saving/PainterSaveGame.h"

// Sets default values
AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);

}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	RightController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
	if (RightController != nullptr)
	{
		RightController->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
		RightController->SetHand(EControllerHand::Right);
	}
	
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Trigger"), IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("Trigger"), IE_Released, this, &AVRPawn::RightTriggerReleased);
	PlayerInputComponent->BindAction(TEXT("Save"), IE_Released, this, &AVRPawn::Save);
	PlayerInputComponent->BindAction(TEXT("Load"), IE_Released, this, &AVRPawn::Load);
}

void AVRPawn::RightTriggerPressed()
{
	if (RightController)
		RightController->TriggerPressed();
}

void AVRPawn::RightTriggerReleased()
{
	if (RightController)
		RightController->TriggerReleased();
}

void AVRPawn::Save()
{
	UPainterSaveGame* Painting = UPainterSaveGame::CreateGame();
	Painting->SetState("Hello!");
	Painting->SerializeFromWorld(GetWorld());
	Painting->Save();
}

void AVRPawn::Load()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load();
	if (Painting) 
	{
		Painting->DeserializeToWorld(GetWorld());
		UE_LOG(LogTemp, Warning, TEXT("Number: %s"), *Painting->GetState());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No save slot present"));
	}
}


