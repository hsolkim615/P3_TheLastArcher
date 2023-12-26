// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"

#include "AI/MonsterAnim.h"
#include "AI/MonsterFSM.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMonsterBase::AMonsterBase()
{

	PrimaryActorTick.bCanEverTick = true;
	
	MonsterFsm = CreateDefaultSubobject<UMonsterFSM>("MonsterFsm");


	ConstructorHelpers::FClassFinder<UMonsterAnim> TempAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/TheLastArchers/KSE/Animations/ABP_NormalMonster.ABP_NormalMonster_C'"));
	if(TempAnim.Succeeded())
	{
		GetMesh()->SetAnimClass(TempAnim.Class);
	}
	// 플레이어를 쳐다보도록한다.
	GetCharacterMovement()->bOrientRotationToMovement = true;
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



