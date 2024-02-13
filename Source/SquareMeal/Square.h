// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Square.generated.h"


UCLASS()
class SQUAREMEAL_API ASquare : public AActor
{
	GENERATED_BODY()

	// Velocity of the Square
	FVector Velocity;

	// Deceleration factor
	float Deceleration;

	float InitialSpeed;

	bool bIfShoot = false;
	
	
public:	
	// Sets default values for this actor's properties
	ASquare();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Shoot(FVector direction);

};
