// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Door"));

	locked = false;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	isOpen = false;
	animating = false;
	firstAngle = GetActorRotation().Quaternion().Euler().Z;
	openSpeed = 3;
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	


	
	

	if (animating) {

		float realTarg = firstAngle + targAngle;

		float currentAngle = GetActorRotation().Quaternion().Euler().Z;

		if (realTarg >= 360) {
			realTarg -= 360;
		} if (realTarg < 0) {
			realTarg += 360;
		}
		if (currentAngle >= 360) {
			currentAngle -= 360;
		}if (currentAngle < 0) {
			currentAngle += 360;
		}

		if (currentAngle> realTarg) {
			AddActorLocalRotation(FQuat(FVector(0, 0, 1), openSpeed * (-PI / 2) * DeltaTime));

		}
		else if (currentAngle < realTarg) {
			AddActorLocalRotation(FQuat(FVector(0, 0, 1), openSpeed *(PI / 2) * DeltaTime));
		}

		if (abs(currentAngle - realTarg) <=5) {
			animating = false;
			SetActorRotation(FQuat(FVector(0, 0, 1), (realTarg / 360) * (2 * PI)));
		}
	}

	

}

void ADoor::Open() {


	if (!locked) {
		animating = true;


		if (!isOpen) {
			targAngle = 270;
			isOpen = true;
		}
		else {
			targAngle = 0;
			isOpen = false;
		}
	}
	else {
		//add the code for a unsuccessful door opening sound
	}
}
