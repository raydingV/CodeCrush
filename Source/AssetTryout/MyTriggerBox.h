// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerBox.h"
#include "Components/StaticMeshComponent.h"
#include "MyTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class ASSETTRYOUT_API AMyTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();
	
public:
	AMyTriggerBox();
	
	UFUNCTION()
	void Event(class AActor* overlappedActor, class AActor* otherActor);

	UPROPERTY(EditAnywhere, Category = "Object to Trigger")
		TSubclassOf<AActor> missile;

	UPROPERTY(EditAnywhere, Category = "Object to Trigger")
	TSubclassOf<AActor> bombVfx;

	UPROPERTY(EditAnywhere, Category = "GameManager")
		AActor* GameManagerActor;

	AGameManager* gameManager;

	FActorSpawnParameters SpawnParams;
	
};
