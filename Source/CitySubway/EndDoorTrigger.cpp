// Fill out your copyright notice in the Description page of Project Settings.


#include "EndDoorTrigger.h"

UEndDoorTrigger::UEndDoorTrigger()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEndDoorTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void UEndDoorTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (const auto Actor : OverlappingActors)
	{
		if (Actor->ActorHasTag(UnlockTag))
		{
			if (Mover && !Mover->GetIsOpen())
			{
				Mover->SetIsOpen(true);
			}
		}
	}
}

void UEndDoorTrigger::SetMover(UEndDoorMover* NewMover)
{
	Mover = NewMover;
	for (auto Element : GetOwner()->GetComponents())
	{
		UE_LOG(LogTemp, Display, TEXT("Name: %s"), *Element->GetName());
	}
	UE_LOG(LogTemp, Display, TEXT("==============="));
}
