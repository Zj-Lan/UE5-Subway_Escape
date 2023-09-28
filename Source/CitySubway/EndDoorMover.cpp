// Fill out your copyright notice in the Description page of Project Settings.


#include "EndDoorMover.h"

// Sets default values for this component's properties
UEndDoorMover::UEndDoorMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEndDoorMover::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ClosedLocation = GetOwner()->GetActorLocation();
	OpenLocation = ClosedLocation - FVector(0,67,0);

	DoorSpeed = FVector::Distance(ClosedLocation, OpenLocation)/20;
}


// Called every frame
void UEndDoorMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsOpen)
	{
		const auto VInterpConstantTo = FMath::VInterpTo(GetOwner()->GetActorLocation(), OpenLocation, DeltaTime, DoorSpeed);
        
		GetOwner()->SetActorLocation(VInterpConstantTo); 
	}
	else
	{
		const auto VInterpConstantTo = FMath::VInterpTo(GetOwner()->GetActorLocation(), ClosedLocation, DeltaTime, DoorSpeed);
        
		GetOwner()->SetActorLocation(VInterpConstantTo); 
	}
	
	// ...
}

void UEndDoorMover::Interact()
{
	SetIsOpen(!bIsOpen);
}

