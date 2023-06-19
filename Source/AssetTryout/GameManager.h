// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyText.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class ASSETTRYOUT_API AGameManager : public AActor
{
	GENERATED_BODY()
    
public:    
	// Sets default values for this actor's properties
	AGameManager();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> ActorToSpawn;

	UFUNCTION(BlueprintCallable, Category = "FirstLetter")
	void FirstLetter(FKey key);

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> MissileActorObject;

	UFUNCTION(BlueprintCallable, Category = "GameOver")
	bool endGame(bool endGameOver);

	bool GameOverEnd;

	UPROPERTY(EditAnywhere)
	AActor* Pawn;

	UPROPERTY()
	TArray<AActor*> SpawnedActors;

	AEnemyText* Enemy;
	AEnemyText* enemyWord;
	AActor* SpawnedActor;
	
	FActorSpawnParameters SpawnParams;
	bool InInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Score;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText ScoreText;

	UPROPERTY(EditAnywhere)
		USoundBase* SoundToFire;
	UPROPERTY(EditAnywhere)
		USoundBase* SoundToWrong;
	UPROPERTY(EditAnywhere)
		USoundBase* SoundNewRound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float CountDownTimer;
	float timerValue;

	
	int CountWord;
	int spawnQue;
	int SpawnMax;
	int randomSpawnWord;
	
	bool readyNewRound;

	
	FText PressedKeyText;
	FString PressedKeyString;
	FString charr;
	
	UPROPERTY(EditAnywhere)
	TArray<FString> Words;
	
	UPROPERTY(EditAnywhere)
	TArray<FString> SpawnWord;

public:    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
