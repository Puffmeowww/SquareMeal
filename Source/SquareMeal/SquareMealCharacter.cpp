// Copyright Epic Games, Inc. All Rights Reserved.

#include "SquareMealCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

//////////////////////////////////////////////////////////////////////////
// ASquareMealCharacter

ASquareMealCharacter::ASquareMealCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void ASquareMealCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Input

void ASquareMealCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Eat behavior
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &ASquareMealCharacter::PlayerInteraction);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASquareMealCharacter::Move);

	}

}

void ASquareMealCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}


//Player Pressed Interaction Key
void ASquareMealCharacter::PlayerInteraction()
{
	
	//If player have square in their stomach
	if (bIfSquare)
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Press with "));
		if (SquareClass != nullptr) // Ensure the bullet class is selected in the editor.
		{
			FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 100); // Spawn in front of the player
			FRotator SpawnRotation = GetActorRotation();

			ASquare* SquareProjectile = GetWorld()->SpawnActor<ASquare>(SquareClass, SpawnLocation, SpawnRotation);
			if (SquareProjectile)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player decide Shoot"));
				SquareProjectile->Shoot(GetActorForwardVector());	
				bIfSquare = false;
				return;
				
			}
		}
	}

	//No square, check ray trace
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Press without "));
		//Check if is square
		FVector StartLocation;
		FVector EndLocation;
		FVector Direction;
		FHitResult HitResult;

		StartLocation = GetActorLocation();
		Direction = GetActorForwardVector();
		EndLocation = StartLocation + Direction * 70.f;
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);
		if (bHit)
		{
			AActor* HitActor = HitResult.GetActor();
			{
				if (HitActor != nullptr)
				{
					// Check if the actor is of type ASquare (or whatever your square actor class is named)
					ASquare* HitSquare = Cast<ASquare>(HitActor);
					if (HitSquare != nullptr)
					{
						HitSquare->Destroy();
						bIfSquare = true;
						return;

					}
				}
			}
		}
	}
	


}



