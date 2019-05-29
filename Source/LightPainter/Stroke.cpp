// Fill out your copyright notice in the Description page of Project Settings.

#include "Stroke.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
AStroke::AStroke()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

}

void AStroke::Update(FVector CursorLocation)
{
	// Update endpoints
	if (StartLocation == FVector::ZeroVector)
	{
		StartLocation = GetActorTransform().InverseTransformPosition(CursorLocation);
	}

	FVector EndPosition = GetActorTransform().InverseTransformPosition(CursorLocation);
	CreateSplineMesh()->SetStartAndEnd(StartLocation, FVector::ZeroVector, EndPosition, FVector::ZeroVector);
	StartLocation = GetActorTransform().InverseTransformPosition(CursorLocation);
}

USplineMeshComponent* AStroke::CreateSplineMesh()
{
	USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
	SplineMesh->SetMobility(EComponentMobility::Movable);
	SplineMesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	SplineMesh->SetStaticMesh(StrokeMesh);
	SplineMesh->SetMaterial(0, StrokeMaterial);
	SplineMesh->SetVisibility(true);
	SplineMesh->RegisterComponent();
	return SplineMesh;
}

