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

    RootComponent = Text;
    
    otherActor = Cast<AMyPawnTo>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyPawnTo::StaticClass()));
    wordCount = 0;
    InFunc = false;
    
    newColor = FColor::White;

}

// Called when the game starts or when spawned
void AEnemyText::BeginPlay()
{
    Super::BeginPlay();
    TargetShoot = false;
    _otherObject = otherActor->GetActorLocation();
    Direction = _otherObject - GetActorLocation();
}

// Called every frame
void AEnemyText::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(otherActor != nullptr)
    {
        SetActorRotation(FRotator(50.0,-90.0,-360.000001));
        // SetActorRotation(FRotator(90.0, Direction.Z, Direction.X));

        AddActorWorldOffset(FVector3d(0.0,Direction.Y,0.0) * DeltaTime * RandomSpeed);    
    }

    FVector thisLocation = GetActorLocation();
    Text->SetText(FText::FromString(chooseWord));
    Text->SetTextRenderColor(newColor);

    if(_otherObject.Y >= thisLocation.Y)
    {
        UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
        this->Destroy();
    }
}