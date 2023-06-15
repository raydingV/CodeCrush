// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemys.h"

#include "MyPawn.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UnrealTypePrivate.h"

// Sets default values
AEnemys::AEnemys()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Distance = 100;
	RandomSpeed = FMath::RandRange(0.1,0.3);

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));

	Text->SetWorldScale3D(FVector(5.0,5.0,5.0));
    
	words = {"Hello", "HhatUP!", "Heyoo", "Nice", "Kind", "Agnostic", "Swift", "zort", "Tea"};

	textWord = words[FMath::RandRange(0,8)];

	Text->SetText(FText::FromString(textWord));

	otherActor = Cast<AMyPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyPawn::StaticClass()));
}

// Called when the game starts or when spawned
void AEnemys::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemys::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(otherActor != nullptr)
	{
		FVector _otherObject = otherActor->GetActorLocation();
		FVector Direction = _otherObject - GetActorLocation();

		SetActorRotation(FRotator(90.0,-90.0,0.0));
		
		AddActorWorldOffset(FVector(0.0, Direction.Y, 0.0) * DeltaTime * RandomSpeed);
	}

}

