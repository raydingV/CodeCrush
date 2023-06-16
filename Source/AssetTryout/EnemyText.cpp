// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyText.h"

#include "MyPawnTo.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UnrealTypePrivate.h"

// Sets default values
AEnemyText::AEnemyText()
{
     // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    Distance = 100;
    RandomSpeed = FMath::RandRange(0.1,0.2);

    Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));

    Text->SetWorldScale3D(FVector(5.0,5.0,5.0));
    
    words = {"merhaba", "UmutluBebek", "KakakCocuk","DombulBebek","SismanBebek", "EmzikliBebek", "LaubaliBebek", "ProBebek"};
    

    otherActor = Cast<AMyPawnTo>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyPawnTo::StaticClass()));
    wordCount = 0;
    InFunc = false;
    
    newColor = FColor::White;
}

// Called when the game starts or when spawned
void AEnemyText::BeginPlay()
{
    Super::BeginPlay();
    chooseWord = words[FMath::RandRange(0,7)];
}

// Called every frame
void AEnemyText::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(otherActor != nullptr)
    {
        FVector _otherObject = otherActor->GetActorLocation();
        Direction = _otherObject - GetActorLocation();

        SetActorRotation(FRotator(50.0,-90.0,-360.000001));
        // SetActorRotation(FRotator(90.0, Direction.Z, Direction.X));

        AddActorWorldOffset(FVector3d(0.0,Direction.Y,0.0) * DeltaTime * RandomSpeed);    
    }

    Text->SetText(FText::FromString(chooseWord));
    Text->SetTextRenderColor(newColor);

}

