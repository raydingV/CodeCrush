// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "EnemyText.h"
#include "Editor/EditorEngine.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/ImportanceSamplingLibrary.h"

// Sets default values
AGameManager::AGameManager()
{
    PrimaryActorTick.bCanEverTick = true;

    CountDownTimer = 1000.0f;
    CountWord = 0;
    spawnQue = 0;
    InInput = false;
    readyNewRound = false;
    Words = {"merhaba", "UmutluBebek", "KakakCocuk","DombulBebek","SismanBebek", "EmzikliBebek", "LaubaliBebek", "ProBebek"};
}

void AGameManager::BeginPlay()
{
    Super::BeginPlay();
    SpawnMax = 4;
    timerValue = 800.0f;
    CountDownTimer = 0;
    SpawnWord = Words;
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CountDownTimer -= DeltaTime * 500;

    if (ActorToSpawn && CountWord < SpawnMax && CountDownTimer <= 0)
    {
        // UE_LOG(LogTemp, Warning, TEXT("The array num: %d"), SpawnWord.Num());
        SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, FVector3d(FMath::RandRange(50.0, 2900.0), FMath::RandRange(2000.0, 3200.0), 60.0) , GetActorRotation(), SpawnParams);

        
        SpawnedActors.Add(SpawnedActor);
        enemyWord = Cast<AEnemyText>(SpawnedActors.Last());

        randomSpawnWord = FMath::RandRange(0, SpawnWord.Num() - 1);
        
        enemyWord->chooseWord = SpawnWord[randomSpawnWord];
        SpawnWord.RemoveAt(randomSpawnWord);
        
        
        // if(SpawnWord.Len() != 0 && enemyWord != nullptr)
        // {
        //     for(int i = 0; SpawnWord.Len(); i++)
        //     {
        //         if(SpawnWord[i] != enemyWord->chooseWord[i])
        //         {
        //             spawnNewWord = false;
        //         }
        //     }
        // }
        // else
        // {
        //     spawnNewWord = true;
        // }
        
        CountDownTimer = timerValue;
        CountWord++;
        spawnQue++;
    }

    if(CountWord < SpawnMax)
    {
        readyNewRound = true;
    }

    if(SpawnedActors.Num() == 0 && readyNewRound)
    {
        SpawnWord.Empty();
        CountWord = 0;
        SpawnMax += 3;
        timerValue -= 200;
        if(SpawnMax > 7)
        {
            SpawnMax = 7;
        }
        if(timerValue < 300)
        {
            timerValue = 300;
        }
        UE_LOG(LogTemp, Warning, TEXT("next Round!"));
        readyNewRound = true;
        SpawnWord = Words;
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
    PressedKeyText = key.GetDisplayName();
    PressedKeyString = PressedKeyText.ToString();

    for(int j = 0; j < spawnQue; j++)
    {
        if(!InInput)
        {
            Enemy = Cast<AEnemyText>(SpawnedActors[j]);
        }
        
        if(PressedKeyString == Enemy->chooseWord.Mid(0,1))
        {
            InInput = true;
            Enemy->TargetShoot = true;
            Enemy->newColor = FColor::Green;
            SpawnedMissileActor = GetWorld()->SpawnActor<AActor>(MissileActorObject, Pawn->GetActorLocation() , Pawn->GetActorRotation(), SpawnParams);
            Enemy->chooseWord.RemoveAt(0 ,1, true);

            if(Enemy->chooseWord.Len() == 0)
            {
                Enemy->K2_DestroyActor();
                spawnQue--;
                InInput = false;
                SpawnedActors.Remove(Enemy);
                break;
            }
        }   
    }
}
