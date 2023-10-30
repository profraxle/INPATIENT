// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Door.generated.h"

UCLASS()
class GIVENAME_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool isOpen;
	float targAngle;
	float firstAngle;
	bool animating;
	int openSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite);
	USoundBase * sound;

	UPROPERTY(EditAnywhere,BlueprintReadWrite);
	USoundBase * lockedNoise;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool locked;


	UBaseInstance* instance;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Open(FVector openedFrom);
};
