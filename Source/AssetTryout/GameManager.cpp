// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "EnemyText.h"
#include "Editor/EditorEngine.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/ImportanceSamplingLibrary.h"

// Sets default values
AGameManager::AGameManager()
{
     // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CountDownTimer = 1000.0f;
    CountWord = 0;
    spawnQue = 0;
    InInput = false;
    readyNewRound = false;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
    Super::BeginPlay();
    SpawnMax = 4;
    timerValue = 800.0f;
    CountDownTimer = 0;
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CountDownTimer -= DeltaTime * 500;

    if (ActorToSpawn && CountWord < SpawnMax && CountDownTimer <= 0)
    {
        FActorSpawnParameters SpawnParams;
        SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, FVector3d(FMath::RandRange(50.0, 2900.0), FMath::RandRange(2000.0, 3200.0), 60.0) , GetActorRotation(), SpawnParams);
        CountDownTimer = timerValue;
        CountWord++;
        spawnQue++;
        
        SpawnedActors.Add(SpawnedActor);
    }

    if(CountWord < SpawnMax)
    {
        readyNewRound = true;
    }

    if(SpawnedActors.Num() == 0 && readyNewRound)
    {
        CountWord = 0;
        SpawnMax += 3;
        timerValue -= 200;
        if(SpawnMax > 10)
        {
            SpawnMax = 10;
        }
        if(timerValue < 300)
        {
            timerValue = 300;
        }
        UE_LOG(LogTemp, Warning, TEXT("next Round!"));
        readyNewRound = false;
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

void AGameManager::FirstLetter(FKey key)
{
    FText PressedKeyText = key.GetDisplayName();
    FString PressedKeyString = PressedKeyText.ToString();
    FString charr;

    for(int j = 0; j < spawnQue; j++)
    {
        if(!InInput)
        {
            Enemy = Cast<AEnemyText>(SpawnedActors[j]);
            UE_LOG(LogTemp, Warning, TEXT ("newCast")); 
        }
        
        if(PressedKeyString == Enemy->chooseWord.Mid(0,1))
        {
            InInput = true;
            Enemy->newColor = FColor::Green;
        }   
    }

    if(InInput)
    {
        for(int i = Enemy->wordCount; i < Enemy->chooseWord.Len(); i++)
        {
            charr = Enemy->chooseWord.Mid(0, 1);
        
            if (charr == PressedKeyString)
            {
                // UE_LOG(LogTemp, Warning, TEXT("%s"), *charr);
                // UE_LOG(LogTemp, Warning, TEXT("Match Press: %s"), *PressedKeyString);
                // UE_LOG(LogTemp, Warning, TEXT("%d Left Letters"), (EnemyInput->chooseWord.Len() - EnemyInput->wordCount));
                Enemy->chooseWord.RemoveAt(0 ,1, true);
                // UE_LOG(LogTemp, Warning, TEXT("%s"), *Enemy->chooseWord);
            }

            if(Enemy->chooseWord.Len() == 0)
            {
                Enemy->K2_DestroyActor();
                spawnQue--;
                InInput = false;
                SpawnedActors.Remove(Enemy);
            }
        }      
    }
}
