// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerEnemy.h"

#include "EnemyText.h"
#include "Editor/EditorEngine.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/ImportanceSamplingLibrary.h"

// Sets default values
ASpawnerEnemy::ASpawnerEnemy()
{
     // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CountDownTimer = 1000.0f;
    CountWord = 0;
    spawnQue = 0;
    InInput = false;
}

// Called when the game starts or when spawned
void ASpawnerEnemy::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASpawnerEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CountDownTimer -= DeltaTime * 500;

    if (ActorToSpawn && CountWord < 8)
    {
        FActorSpawnParameters SpawnParams;
        SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, FVector3d(FMath::RandRange(50.0, 2900.0), FMath::RandRange(2000.0, 3200.0), 60.0) , GetActorRotation(), SpawnParams);
        CountDownTimer = 1000.0f;
        CountWord++;
        
        SpawnedActors.Add(SpawnedActor);
        
    }
    

    // if(SpawnedActors[spawnQue] != nullptr)
    // {
    //     Enemy = Cast<AEnemyText>(SpawnedActors[spawnQue]);
    // }
    // else
    // {
    //     UGameplayStatics::SetGamePaused(GetWorld(), true);
    // }
    
}

void ASpawnerEnemy::FirstLetter(FKey key)
{
    FText PressedKeyText = key.GetDisplayName();
    FString PressedKeyString = PressedKeyText.ToString();
    FString charr;

    for(int j = 0; j < CountWord; j++)
    {
        if(!InInput)
        {
            Enemy = Cast<AEnemyText>(SpawnedActors[j]);
        }

        if(Enemy != nullptr && PressedKeyString == Enemy->chooseWord.Mid(0,1))
        {
            InInput = true;
            Enemy->newColor = FColor::Green;        }
    }

    if(InInput)
    {
        for(int i = Enemy->wordCount; i < Enemy->chooseWord.Len(); i++)
        {
            charr = Enemy->chooseWord.Mid(0, 1);
        
            if (charr == PressedKeyString)
            {
                UE_LOG(LogTemp, Warning, TEXT("%s"), *charr);
                // UE_LOG(LogTemp, Warning, TEXT("Match Press: %s"), *PressedKeyString);
                // UE_LOG(LogTemp, Warning, TEXT("%d Left Letters"), (EnemyInput->chooseWord.Len() - EnemyInput->wordCount));
                Enemy->chooseWord.RemoveAt(0 ,1, true);
                UE_LOG(LogTemp, Warning, TEXT("%s"), *Enemy->chooseWord);
            }

            if(Enemy->chooseWord.Len() == 0)
            {
                Enemy->K2_DestroyActor();
                spawnQue++;
                InInput = false;
            }
        }      
    }
}
