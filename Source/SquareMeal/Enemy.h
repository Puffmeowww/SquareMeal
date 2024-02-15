// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class SQUAREMEAL_API AEnemy : public AActor
{
	GENERATED_BODY()

public:

	// Patrol points
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol Points")
	FVector PatrolPointA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol Points")
	FVector PatrolPointB;

	// Patrol speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	float Speed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	bool isStunned = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	int Score = 100;


private:
	FVector CurrentTarget;

	FTimerHandle StunTimerHandle;

public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SwitchPatrolPoint();

	UFUNCTION(BlueprintCallable)
	void GetHurt();

	UFUNCTION(BlueprintCallable)
	void Recover();

};
