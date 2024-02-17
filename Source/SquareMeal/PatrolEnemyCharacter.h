// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PatrolEnemyCharacter.generated.h"

UCLASS()
class SQUAREMEAL_API APatrolEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APatrolEnemyCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	bool isStunned = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	int Score = 100;

	FTimerHandle StunTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void GetHurt();

	UFUNCTION(BlueprintCallable)
	void Recover();

};
