// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/AudioComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{

	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	//// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;


}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	instance = Cast<UBaseInstance>(GetGameInstance());

	dVolume = instance->SoundVolume;

	humming = UGameplayStatics::CreateSound2D(this,sound,0.4*dVolume,1,0);
	creepy = UGameplayStatics::CreateSound2D(this, creepSound, 0.05 * dVolume, 1, 0);
	humming->Play();
	FadeFromBlack();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (day >= 4 && day !=7) {
		if (creepy) {
			if (!creepy->IsPlaying()) {
				creepy->Play();
				creepy->SetVolumeMultiplier(0.05 * instance->SoundVolume * day);
			}
		}
	}
	if (day == 7) {

		if (humming) {
			if (humming->IsPlaying()) {
				humming->Stop();
			}
		}
		
	}

	if (dVolume != instance->SoundVolume)
	{
		dVolume = instance->SoundVolume;
		humming->SetVolumeMultiplier(0.4* instance->SoundVolume);
		creepy->SetVolumeMultiplier(0.05 * instance->SoundVolume * day);
	}

	if (fadeTrigger) {
		FadeToBlack();
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		//Interaction
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::Interact);
	}

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y * 0.5f);
		AddMovementInput(GetActorRightVector(), MovementVector.X * 0.5f);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Interact(const FInputActionValue& Value) {

	APlayerCameraManager* OurCamera = UGameplayStatics::GetPlayerCameraManager(this, 0);

	FCollisionQueryParams parameters;

	FHitResult OutHit;

	GetWorld()->LineTraceSingleByChannel(OutHit, OurCamera->GetCameraLocation(), OurCamera->GetCameraLocation() + OurCamera->GetActorForwardVector() * 300, ECC_Visibility, parameters);

	AActor * hitActor = OutHit.GetActor();

	if (hitActor) {
		if (hitActor->ActorHasTag("Door")) {
			ADoor* door = Cast<ADoor>(hitActor);

			door->Open(GetActorLocation());
			
		}

		if (hitActor->ActorHasTag("Interact")) {
			AInteractActor* interact = Cast<AInteractActor>(hitActor);

			interact->InteractedWith();
		}

		if (hitActor->ActorHasTag("Hurt")) {

			RedVision();

		}
	}
}

