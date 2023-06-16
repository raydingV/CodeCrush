// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnTo.h"

// Sets default values
AMyPawnTo::AMyPawnTo()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyPawnTo::BeginPlay()
{
	Super::BeginPlay();

	enemySpawner = Cast<ASpawnerEnemy>(Actor);
}

// Called every frame
void AMyPawnTo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(enemySpawner != nullptr)
	{
		if(enemySpawner->Enemy != nullptr)
		{
			Direct = enemySpawner->Enemy->GetActorLocation() - GetActorLocation();
			Direct.Normalize(-1.0f);
			FRotator TargetRotation = FRotationMatrix::MakeFromX(Direct).Rotator();
			TargetRotation.Yaw -= 90.0f;
			
			SetActorRotation(TargetRotation);
		}
	}
}

// Called to bind functionality to input
void AMyPawnTo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

