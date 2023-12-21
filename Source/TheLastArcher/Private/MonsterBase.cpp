// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include "AI/MonsterFSM.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
AMonsterBase::AMonsterBase()
{

	PrimaryActorTick.bCanEverTick = true;
	MonsterFsm = CreateDefaultSubobject<UMonsterFSM>("MonsterFsm");
}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



