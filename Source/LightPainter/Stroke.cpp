// Fill out your copyright notice in the Description page of Project Settings.

#include "Stroke.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
AStroke::AStroke()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	StrokeMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("StrokeMeshes"));
	StrokeMeshes->SetupAttachment(Root);

}

void AStroke::Update(FVector CursorLocation)
{
	FVector LocalCursorLocation = GetActorTransform().InverseTransformPosition(CursorLocation);
	FTransform StrokeTransform = FTransform(LocalCursorLocation);
	StrokeMeshes->AddInstance(StrokeTransform);
	StartLocation = LocalCursorLocation;
}

