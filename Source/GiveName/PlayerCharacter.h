// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "BaseInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Door.h"
#include "InteractActor.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;

UCLASS()
class GIVENAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;


public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void RedVision();

	UFUNCTION(BlueprintImplementableEvent)
	void FadeToBlack();

	UFUNCTION(BlueprintImplementableEvent)
	void FadeFromBlack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool fadeTrigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Control|Input Actions") UInputAction* MyAction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite);
	UAudioComponent  * humming;

protected:
	//UCameraComponent* camera;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USoundBase * sound;
	
	float dVolume;

	UBaseInstance* instance;
	

};
