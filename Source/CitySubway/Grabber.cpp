// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// const auto CompactString = GetComponentRotation().ToCompactString();
	//
	// UE_LOG(LogTemp, Display, TEXT("%s, Time: %f"), *CompactString, GetWorld()->TimeSeconds);
	
	if (PhysicsHandle != nullptr && PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->SetTargetLocationAndRotation(
			GetComponentLocation() + 50 * GetForwardVector(),
			GetComponentRotation()
		);
	}	
	
}

void UGrabber::GrabPressed()
{
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() == nullptr)
	{
		ToGrab();
	}
	else
	{
		ToDrop();
	}
	
}

void UGrabber::GrabReleased()
{
	UE_LOG(LogTemp, Display, TEXT("UGrabber::Release()"));
}

void UGrabber::InteractPressed()
{
	ToInteract();
}

void UGrabber::InteractReleased()
{
	UE_LOG(LogTemp, Display, TEXT("InteractReleased"));
}

void UGrabber::ToGrab() const
{
	const auto ComponentLocation = GetComponentLocation();
	const FVector EndLocation = ComponentLocation+400*GetForwardVector();

	FHitResult HitResult;
	bool isHit = GetWorld()->SweepSingleByChannel(
		HitResult, ComponentLocation, EndLocation,
		FQuat::Identity, ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(30)
		);

	UE_LOG(LogTemp, Display, TEXT("isHit: %d"), isHit);
	if (isHit)
	{
		UE_LOG(LogTemp, Display, TEXT("Hit Name: %s"), *HitResult.GetActor()->GetName());
		// DrawDebugLine(GetWorld(), ComponentLocation, EndLocation, FColor::Red, true, -1, 0, 20);
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, true);

		HitResult.GetComponent()->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(), NAME_None, HitResult.ImpactPoint,
			GetComponentRotation()
		);
		
		// DrawDebugLine(GetWorld(), ComponentLocation, HitResult.Location, FColor::Green, true);
		// DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, true);
		//
		// DrawDebugLine(GetWorld(), ComponentLocation, HitResult.ImpactPoint, FColor::Red, true);
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, true);
	}
}

void UGrabber::ToDrop() const
{
	if (UPrimitiveComponent* GrabbedComponent = PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->ReleaseComponent();
		GrabbedComponent->WakeAllRigidBodies();
		GrabbedComponent->AddImpulse(300 * GetForwardVector() + 300 * GetUpVector(), NAME_None, true);
	}
}

void UGrabber::ToInteract()
{
	const auto ComponentLocation = GetComponentLocation();
	const FVector EndLocation = ComponentLocation+100*GetForwardVector();

	FHitResult HitResult;
	bool isHit = GetWorld()->SweepSingleByChannel(
		HitResult, ComponentLocation, EndLocation,
		FQuat::Identity, ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(30)
		);

	if (isHit)
	{
		UE_LOG(LogTemp, Display, TEXT("hit"));
		UE_LOG(LogTemp, Display, TEXT("Name: %s"), *HitResult.GetActor()->GetName());

		// DrawDebugLine(GetWorld(), ComponentLocation, EndLocation, FColor::Red, true);
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, true);
		
		if (const auto PlaySoundComponent = HitResult.GetActor()->GetComponentByClass(UPlaySound::StaticClass()))
		{
			Cast<UPlaySound>(PlaySoundComponent)->Interact();
		}
		else if (const auto EndDoorMoverComponent = HitResult.GetActor()->GetComponentByClass(UEndDoorMover::StaticClass()))
		{
			Cast<UEndDoorMover>(EndDoorMoverComponent)->Interact();
		}
		
		// for (const auto component : HitResult.GetActor()->GetComponents())
		// {
		// 	if (component->GetFName() == TEXT("PlaySound"))
		// 	{
		// 		Cast<UPlaySound>(component)->Interact();
		// 	}
		// 	else if (component->GetFName() == TEXT("EndDoorMover"))
		// 	{
		// 		Cast<UEndDoorMover>(component)->Interact();
		// 	}
		// 	//else if TODO
		// }		
	}
}

