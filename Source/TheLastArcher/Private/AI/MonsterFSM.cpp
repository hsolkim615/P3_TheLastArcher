// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MonsterFSM.h"

#include "AsyncTreeDifferences.h"
#include "MonsterBase.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UMonsterFSM::UMonsterFSM()
{

	PrimaryComponentTick.bCanEverTick = true;
	
	
}


// Called when the game starts
void UMonsterFSM::BeginPlay()
{
	Super::BeginPlay();

	Self = Cast<AMonsterBase>(GetOwner());
	
}


// Called every frame
void UMonsterFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 내상태 따라 각 일을 처리하고싶다.
	switch (State)
	{
	case EMonsterState::Idle:   TickIdle();    break;
	case EMonsterState::Move:   TickMove();    break;
	case EMonsterState::Attack: TickAttack();  break;
	case EMonsterState::Damage: TickDamage();  break;
	case EMonsterState::Die:    TickDie();	   break;
	}
}

void UMonsterFSM::TickIdle()
{
	// 플레이어를 찾고 싶다, 목적지를 플레이어로 기억하고싶다.
	Target = Cast<ACharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// 만약 찾았다면 (조건)
	if(Target != nullptr)
	{
		// 이동 상태로 전이하고싶다.
		State = EMonsterState::Move; // 전이
	}
	
	
}

void UMonsterFSM::TickMove()
{
	// 목적지를 향해 이동하고싶다.
	FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	Self->AddMovementInput(Direction);
	// 공격 가능 거리라면
	
	// 공격 상태로 전이하고싶다.
}

void UMonsterFSM::TickAttack()
{
	 
}

void UMonsterFSM::TickDamage()
{
}

void UMonsterFSM::TickDie()
{
}

