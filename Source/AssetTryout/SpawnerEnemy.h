// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyText.h"
#include "GameFramework/Actor.h"
#include "SpawnerEnemy.generated.h"

UCLASS()
class ASSETTRYOUT_API ASpawnerEnemy : public AActor
{
	GENERATED_BODY()
    
public:    
	// Sets default values for this actor's properties
	ASpawnerEnemy();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> ActorToSpawn;

	UFUNCTION(BlueprintCallable, Category = "FirstLetter")
	void FirstLetter(FKey key);

	UPROPERTY()
	TArray<AActor*> SpawnedActors;

	AEnemyText* Enemy;
	AActor* SpawnedActor;
	int zort;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float CountDownTimer;
	int CountWord;
	int spawnQue;
	int InputQue;
	bool InInput;

public:    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
