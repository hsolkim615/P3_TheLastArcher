// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MonsterFSM.h"

#include "AsyncTreeDifferences.h"
#include "ComponentSourceInterfaces.h"
#include "MonsterBase.h"
#include "Player_Archer.h"
#include "AI/MonsterAnim.h"
#include "Kismet/KismetMathLibrary.h"


UMonsterFSM::UMonsterFSM()
{

	PrimaryComponentTick.bCanEverTick = true;
	
	
}


// Called when the game starts
void UMonsterFSM::BeginPlay()
{
	Super::BeginPlay();

	// 나의 주인이 누군지 알거라.
	Self = Cast<AMonsterBase>(GetOwner());

	MonsterAnim = Cast<UMonsterAnim>(Self->GetMesh()->GetAnimInstance());
	
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
	UE_LOG(LogTemp,Warning,TEXT("Idle!"))
	// 플레이어를 찾고 싶다, 목적지를 플레이어로 기억하고싶다.
	Target = Cast<APlayer_Archer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	// 만약 찾았다면 (조건)
	if(Target != nullptr)
	{
		// 이동 상태로 전이하고싶다.
		SetState(EMonsterState::Move); // 전이
	}

	
}

void UMonsterFSM::TickMove()
{
	UE_LOG(LogTemp,Warning,TEXT("Move!"))
	// 목적지를 향해 이동하고싶다.
	FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	
	Self->AddMovementInput(Direction.GetSafeNormal());

	// 공격 가능 거리라면
	if(Direction.Length() <= AttackRange)
	{
		// 공격 상태로 전이하고싶다.
		SetState(EMonsterState::Attack);
		CurrentTime = AttackTime;
	}
	
	
}

void UMonsterFSM::TickAttack()
{
	// Attack Wait
	CurrentTime += GetWorld()->GetDeltaSeconds();
	// 공격쿨타임이 되면
	if(CurrentTime > AttackTime)
	{
		// 공격 애니메이션을 키고
		MonsterAnim->IsAttack = true;
		CurrentTime = 0;
		// 공격범위를 벗어나면
		if(AttackRange > Target->GetActorLocation().Length())
		{
			// 타겟을 쫓고 쫓을 때는 공격하지 않도록 할것이다.
			SetState(EMonsterState::Move);
			MonsterAnim->IsAttack = false;
		}
		// 공격 범위를 벗어나지 않았으면
		else
		{
			// 공격한다.
			UE_LOG(LogTemp,Warning,TEXT("Attack!"));
		}
	}
}

void UMonsterFSM::TickDamage()
{
	CurrentTime += GetWorld()->GetDeltaSeconds();
	// 2초동안 대기 했다가
	if(CurrentTime > DamageTime)
	{
		// 맞는 애니메이션을 하고
		PlayMontageHitted();
		UE_LOG(LogTemp,Warning,TEXT("Hitted!"));
		// 이동상태로 전이 하고싶다.
		SetState(EMonsterState::Move);
	}
	
}

void UMonsterFSM::TickDie()
{
	PlayMontageDie();
	UE_LOG(LogTemp,Warning,TEXT("Hitted!"));
	CurrentTime += GetWorld()->GetDeltaSeconds();
	if(CurrentTime>Dietime)
	{
		// 2초동안 대기 했다각
		// 애니메이션을 작동하고 죽고싶다.
		Self->Destroy();
	}
	
}

void UMonsterFSM::PlayMontageHitted()
{
	Self->PlayAnimMontage(MonsterMontage,1,TEXT("Hitted"));
}

void UMonsterFSM::PlayMontageDie()
{
	Self->PlayAnimMontage(MonsterMontage,1,TEXT("Died"));
}

void UMonsterFSM::SetState(EMonsterState Next)
{
	State = Next;
	MonsterAnim-> State = Next; 
	CurrentTime = 0;
}

