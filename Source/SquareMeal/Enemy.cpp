// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentTarget = PatrolPointA;

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isStunned == false)
	{
		FVector Direction = CurrentTarget - GetActorLocation();
		Direction.Normalize();
		FVector NewLocation = GetActorLocation() + (Direction * Speed * DeltaTime);
		SetActorLocation(NewLocation);

		if (FVector::Distance(GetActorLocation(), CurrentTarget) < 100.0f)
		{
			SwitchPatrolPoint();
		}

		//FRotator NewRotation = Direction.Rotation();
		//SetActorRotation(NewRotation);
	}


}

void AEnemy::SwitchPatrolPoint()
{
	if (CurrentTarget == PatrolPointA)
		CurrentTarget = PatrolPointB;
	else
		CurrentTarget = PatrolPointA;
}

void AEnemy::GetHurt()
{

	isStunned = true;

	GetWorld()->GetTimerManager().SetTimer(StunTimerHandle, this, &AEnemy::Recover, 3.0f, false);

}

void AEnemy::Recover()
{
	isStunned = false;
}

