// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EndDoorMover.h"
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndDoorTrigger.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CITYSUBWAY_API UEndDoorTrigger : public UBoxComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UEndDoorTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMover(UEndDoorMover* NewMover);

private:
	UPROPERTY(EditAnywhere)
	FName UnlockTag;

	UEndDoorMover* Mover;
};
