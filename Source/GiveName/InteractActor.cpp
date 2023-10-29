// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor.h"

// Sets default values
AInteractActor::AInteractActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Interact"));

}

// Called when the game starts or when spawned
void AInteractActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AInteractActor::InteractedWith() {
//
//}

//FUNCTION InteractedWith
/*
	Get the monitor
	If id is equal to the monitors current index
	Change the monitors current index
	Delete this object if desired
*/

