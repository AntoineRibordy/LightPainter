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
	JointMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("JointMeshes"));
	JointMeshes->SetupAttachment(Root);

}

void AStroke::Update(FVector CursorLocation)
{
	if (StartLocation.IsNearlyZero())
	{
		StartLocation = CursorLocation;
		JointMeshes->AddInstance(GetNextJointTransform(CursorLocation));
	}
	FVector LocalCursorLocation = GetActorTransform().InverseTransformPosition(CursorLocation);
	StrokeMeshes->AddInstance(GetNextSegmentTransform(CursorLocation));
	// We want to add the instance at the joint, with no rotation and a scale of 1(?)
	JointMeshes->AddInstance(GetNextJointTransform(CursorLocation));
	StartLocation = CursorLocation;
}

FTransform AStroke::GetNextSegmentTransform(FVector CurrentLocation) const
{
	FTransform SegmentTransform;

	SegmentTransform.SetScale3D(GetNextSegmentScale(CurrentLocation));
	SegmentTransform.SetRotation(GetNextSegmentRotation(CurrentLocation));
	SegmentTransform.SetLocation(GetNextSegmentLocation(CurrentLocation));

	return SegmentTransform;
}

FTransform AStroke::GetNextJointTransform(FVector CurrentLocation) const
{
	FTransform JointTransform;
	JointTransform.SetLocation(GetTransform().InverseTransformPosition(CurrentLocation));
	return JointTransform;
}

FVector AStroke::GetNextSegmentScale(FVector CurrentLocation) const
{
	// Calculate the distance between StartLocation and CurrentLocation
	float SegmentSize = (CurrentLocation - StartLocation).Size();
	return FVector(SegmentSize, 1, 1);
}

FQuat AStroke::GetNextSegmentRotation(FVector CurrentLocation) const
{
	// Get the angle between the forward vector and the vector from currentlocation and startlocation
	FVector InstanceNormal = FVector::ForwardVector;
	FVector SegmentNormal = (CurrentLocation - StartLocation).GetSafeNormal();
	return FQuat::FindBetweenNormals(InstanceNormal, SegmentNormal);
}

FVector AStroke::GetNextSegmentLocation(FVector CurrentLocation) const
{
	return GetTransform().InverseTransformPosition(StartLocation);
}

