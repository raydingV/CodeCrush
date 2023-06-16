// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "Materials/MaterialInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "EnemyText.generated.h"

UCLASS()
class ASSETTRYOUT_API AEnemyText : public AActor
{
	GENERATED_BODY()
    
public:    
	// Sets default values for this actor's properties
	AEnemyText();

	// UFUNCTION()
	// void FirstLetterInput(FString key);
    
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* Text;

	UPROPERTY(EditAnywhere)
	AActor* otherActor;

	UPROPERTY(EditAnywhere)
	TArray<FString> words;

	UPROPERTY(EditAnywhere)
	FString chooseWord;

	FVector Direction;
	float Distance;
	float RandomSpeed;
	int wordCount;
	int Queue;
	bool InFunc;
	FColor newColor;
    

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
