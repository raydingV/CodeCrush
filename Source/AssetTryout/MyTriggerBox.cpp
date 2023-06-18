// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTriggerBox.h"


AMyTriggerBox::AMyTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AMyTriggerBox::Event);
}

void AMyTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

void AMyTriggerBox::Event(AActor* overlappedActor, AActor* otherActor)
{
	if(otherActor && otherActor != nullptr)
	{
		otherActor->Destroy();
	}
}

