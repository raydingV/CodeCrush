// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorSpawn.h"

// Sets default values
AMyActorSpawn::AMyActorSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CountDownTimer = 1000.0f;
	WordCounter = 0;
}

// Called when the game starts or when spawned
void AMyActorSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActorSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CountDownTimer -= DeltaTime * 500;
	
	if (ActorToSpawn && CountDownTimer <= 0 && WordCounter <= 6)
	{
		FActorSpawnParameters SpawnParams;
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, FVector3d(FMath::RandRange(50.0, 2900.0), FMath::RandRange(2000.0, 3300.0), 70.0) , GetActorRotation(), SpawnParams);
		AMyActorSpawn* SpawnedObject = Cast<AMyActorSpawn>(SpawnedActor);
		WordCounter++;
		CountDownTimer = 1000.0f;
		SpawnedObjectsArray.Add(SpawnedObject);
	}
}

