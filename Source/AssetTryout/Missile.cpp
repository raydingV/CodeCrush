// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"
#include "EnemyText.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GameManagerObject = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	GameManager = Cast<AGameManager>(GameManagerObject);

	hitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = hitBox;
	
	hitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	hitBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	hitBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	// Bind the OnActorBeginOverlap function to the overlap event
	hitBox->OnComponentBeginOverlap.AddDynamic(this, &AMissile::OnComponentBeginOverlap);
	
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
	animRoll = 0;
	_otherObject = GameManager->Enemy->GetActorLocation();
	Direction = _otherObject - GetActorLocation();
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	animRoll += DeltaTime;
	
	TargetRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	
	TargetRotation.Yaw -= 90.0f;
			
	SetActorRotation(TargetRotation);

	AddActorWorldOffset(Direction * DeltaTime * 1.8);

	FVector thisLoc = GetActorLocation();
	FVector _otherObjectUpdate = GameManager->Enemy->GetActorLocation();
	
	float distance = FMath::Abs(_otherObjectUpdate.X - thisLoc.X);

	if(GameManager->Enemy != nullptr)
	{
		if(_otherObjectUpdate.Y >= thisLoc.Y && distance <= 300)
		{
			// if(GameManager->Enemy->chooseWord.Len() == 0)
			// {
			// 	GetWorld()->SpawnActor<AActor>(explosionVFX, GameManager->Enemy->GetActorLocation() , GameManager->Enemy->GetActorRotation(), SpawnParams);
			// }
			GameManager->Enemy->SetActorLocation(FVector(GameManager->Enemy->GetActorLocation().X, GameManager->Enemy->GetActorLocation().Y - 50, GameManager->Enemy->GetActorLocation().Z));
			GetWorld()->SpawnActor<AActor>(bombVfx, GetActorLocation() , GetActorRotation(), SpawnParams);
			this->Destroy();
		}

		else if(thisLoc.Y >= 3000)
		{
			this->Destroy();
		}
	}

}

void AMissile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

