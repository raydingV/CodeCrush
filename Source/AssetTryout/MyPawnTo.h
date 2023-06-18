// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "GameFramework/Pawn.h"
#include "MyPawnTo.generated.h"

UCLASS()
class ASSETTRYOUT_API AMyPawnTo : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawnTo();
	
	AGameManager* enemySpawner;
	FVector Direct;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	AActor* Actor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
