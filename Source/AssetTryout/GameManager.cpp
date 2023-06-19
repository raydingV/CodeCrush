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
    Words = {"submit", "five", "return", "things", "words", "extra", "wave", "yes", "little", "panic", "cyber", "man", "star", "curse"};
    GameOverEnd = false;
}

void AGameManager::BeginPlay()
{
    Super::BeginPlay();
    SpawnMax = 4;
    timerValue = 800.0f;
    CountDownTimer = 500;
    SpawnWord = Words;
    Score = 0;
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CountDownTimer -= DeltaTime * 300;

    if (ActorToSpawn && CountWord < SpawnMax && CountDownTimer <= 0)
    {
        // UE_LOG(LogTemp, Warning, TEXT("The array num: %d"), SpawnWord.Num());
        SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, FVector3d(FMath::RandRange(-850.0, 820.0), FMath::RandRange(-3100.0, -1600.0), 60.0) , GetActorRotation(), SpawnParams);

        
        SpawnedActors.Add(SpawnedActor);
        enemyWord = Cast<AEnemyText>(SpawnedActors.Last());

        randomSpawnWord = FMath::RandRange(0, SpawnWord.Num() - 1);
        
        enemyWord->chooseWord = SpawnWord[randomSpawnWord];
        SpawnWord.RemoveAt(randomSpawnWord);
        CountDownTimer = timerValue;
        CountWord++;
        spawnQue++;
    }

    if(CountWord >= SpawnMax)
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
        readyNewRound = false;
        SpawnWord = Words;
    }

    ScoreText = FText::Format(FText::FromString("Score: {0}"), FText::AsNumber(Score));   
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
            Enemy->newColor = FColor::Red;
            GetWorld()->SpawnActor<AActor>(MissileActorObject, Pawn->GetActorLocation() , Pawn->GetActorRotation(), SpawnParams);
            Enemy->chooseWord.RemoveAt(0 ,1, true);
            Score += 50;
            UGameplayStatics::PlaySound2D(GetWorld(), SoundToFire);

            if(Enemy->chooseWord.Len() == 0)
            {
                Enemy->Destroy();
                spawnQue--;
                InInput = false;
                SpawnedActors.Remove(Enemy);
                break;
            }
        }
        else if(PressedKeyString != Enemy->chooseWord.Mid(0, 1))
        {
            UGameplayStatics::PlaySound2D(GetWorld(), SoundToWrong);
        }
    }
}

bool AGameManager::endGame(bool endGameOver)
{
    endGameOver = GameOverEnd;
    return endGameOver;
}
