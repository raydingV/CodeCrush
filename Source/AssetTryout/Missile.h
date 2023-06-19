// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "Components/BoxComponent.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "Missile.generated.h"

UCLASS()
class ASSETTRYOUT_API AMissile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissile();
	
	UPROPERTY()
	AActor* otherActor;

	UPROPERTY()
	FVector Direction;

	UPROPERTY(EditAnywhere)
	AActor* GameManagerObject;

	AGameManager* GameManager;

	float animRoll;
	FRotator TargetRotation;

	UPROPERTY(EditAnywhere, Category = "Object to Trigger")
	TSubclassOf<AActor> bombVfx;

	UPROPERTY(EditAnywhere, Category = " Object to Trigger")
	TSubclassOf<AActor> explosionVFX;

	FActorSpawnParameters SpawnParams;
	
	FVector _otherObject;

	UPROPERTY(EditAnywhere)
		USoundBase* SoundToHit;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
