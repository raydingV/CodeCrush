// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "Components/BoxComponent.h"
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

	UFUNCTION(BlueprintCallable, Category = "AnimationDestroy")
	void animDestroy(USkeletalMeshComponent* actor, USkeletalMeshComponent* actorRegular, USkeletalMeshComponent* actorSpeed);

	UFUNCTION(BlueprintCallable, Category = "AnimationSet")
	void animSet(USkeletalMeshComponent* actorSlow, USkeletalMeshComponent* actorRegular, USkeletalMeshComponent* actorSpeed);
	
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* Text;

	UPROPERTY(EditAnywhere)
	AActor* otherActor;

	UPROPERTY(EditAnywhere)
	FString chooseWord;

	FVector Direction;
	
	float Distance;
	float RandomSpeed;

	int wordCount;
	int Queue;
	
	bool InFunc;
	bool TargetShoot;
	
	FColor newColor;

	FActorSpawnParameters SpawnParams;
	
	AActor* bombVfx;
	
	FVector _otherObject;

	FVector thisLocation;

	UFUNCTION(BlueprintCallable, Category = "GameOver")
		void endGame();

	
    

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
