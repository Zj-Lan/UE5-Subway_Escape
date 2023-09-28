// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndDoorMover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CITYSUBWAY_API UEndDoorMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEndDoorMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	[[nodiscard]] bool GetIsOpen() const
	{
		return bIsOpen;
	}
	
	void SetIsOpen(const bool Open)
	{
		this->bIsOpen = Open;
	}

	void Interact();

private:
	FVector ClosedLocation;
	FVector OpenLocation;

	UPROPERTY(EditAnywhere)
	bool bIsOpen;

private:
	float DoorSpeed;
};
