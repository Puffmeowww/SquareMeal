// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolEnemyCharacter.h"

// Sets default values
APatrolEnemyCharacter::APatrolEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APatrolEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrolEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APatrolEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APatrolEnemyCharacter::GetHurt()
{

	isStunned = true;

	GetWorld()->GetTimerManager().SetTimer(StunTimerHandle, this, &APatrolEnemyCharacter::Recover, 3.0f, false);

}

void APatrolEnemyCharacter::Recover()
{
	isStunned = false;
}



