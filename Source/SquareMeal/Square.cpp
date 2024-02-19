// Fill out your copyright notice in the Description page of Project Settings.


#include "Square.h"

// Sets default values
ASquare::ASquare()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Velocity = FVector::ZeroVector;
	Deceleration = 0.97f;
	InitialSpeed = 2000.0f;

}

// Called when the game starts or when spawned
void ASquare::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASquare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIfShoot)
	{
		FVector NewLocation = GetActorLocation() + (Velocity * DeltaTime);
		SetActorLocation(NewLocation);

		Velocity *= Deceleration;

		if (Velocity.Size() < 1.0f)
		{
			Velocity = FVector::ZeroVector;
		}
	}

}

void ASquare::Shoot(FVector direction)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("Shoot"));
	Velocity = direction * InitialSpeed;
	bIfShoot = true;
}
