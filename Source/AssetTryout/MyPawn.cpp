// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "InputCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void AMyPawn::textFunc(FKey Key)
{
	// for(int i = 0, i < spawnClass->SpawnedObjectsArray.Num(), i++)
	// {
	// 	
	// }
	
	 UE_LOG(LogTemp, Error, TEXT("haha"));
}



