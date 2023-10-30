// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseInstance.generated.h"

/**
 * 
 */
UCLASS()
class GIVENAME_API UBaseInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite);
	float SoundVolume;
	
};
