// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaySound.h"

// Sets default values for this component's properties
UPlaySound::UPlaySound()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlaySound::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlaySound::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlaySound::Interact() const
{
	if (AudioSource == nullptr)
	{
		return;
	}

	if (AudioSource->GetPlayState()==EAudioComponentPlayState::Stopped)
	{
		AudioSource->FadeIn(2);
	}
	else
	{
		AudioSource->SetPaused(!AudioSource->bIsPaused);
	}
	
}

