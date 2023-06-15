#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "Materials/MaterialInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Enemys.generated.h"

UCLASS()
class ASSETTRYOUT_API AEnemys : public AActor
{
	GENERATED_BODY()
    
public:    
	// Sets default values for this actor's properties
	AEnemys();

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* Text;

	UPROPERTY(EditAnywhere)
	AActor* otherActor;

	UPROPERTY(EditAnywhere)
	TArray<FString> words;

	UPROPERTY(EditAnywhere)
		FString textWord;
    
    

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float Distance;
	float RandomSpeed;

public:    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};