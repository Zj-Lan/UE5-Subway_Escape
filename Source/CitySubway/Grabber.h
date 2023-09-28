// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PlaySound.h"
#include "EndDoorMover.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

class UPhysicsHandleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CITYSUBWAY_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void GrabPressed();
	
	UFUNCTION(BlueprintCallable)
	void GrabReleased();

	UFUNCTION(BlueprintCallable)
	void InteractPressed();
	
	UFUNCTION(BlueprintCallable)
	void InteractReleased();

	UFUNCTION(BlueprintImplementableEvent)
	void InteractEvent();

private:
	void ToGrab() const;
	void ToDrop() const;
	void ToInteract();

	UPhysicsHandleComponent* PhysicsHandle;
		
};
