// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActorSpawn.generated.h"

UCLASS()
class ASSETTRYOUT_API AMyActorSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActorSpawn();


	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float CountDownTimer;
	int WordCounter;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TArray<AMyActorSpawn*> SpawnedObjectsArray;
	

		
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<AActor> ActorToSpawn;

};

