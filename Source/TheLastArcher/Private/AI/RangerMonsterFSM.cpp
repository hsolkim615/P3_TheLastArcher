// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RangerMonsterFSM.h"

#include "AIController.h"
#include "MonsterBase.h"
#include "AI/MonsterAnim.h"
#include "AI/MonsterArrowActor.h"
#include "Components/ArrowComponent.h"


URangerMonsterFSM::URangerMonsterFSM()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URangerMonsterFSM::BeginPlay()
{
	Super::BeginPlay();
}

void URangerMonsterFSM::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
}

void URangerMonsterFSM::TickAttack()
{
	UE_LOG(LogTemp,Warning,TEXT("RangeAttack!"));
	CurrentTime += GetWorld()->GetDeltaSeconds();
	if(CurrentTime > AttackTime)
	{
		//MonsterAnim->IsAttack = true;
		CurrentTime = 0;
		float Dist = FVector::Dist(Self->GetActorLocation(),Target->GetActorLocation());
		if(Dist>AttackRange)
		{
			SetState(EMonsterState::Move);
			MonsterAnim->IsAttack = false;
		}
		else
		{
			Ai->SetFocus(Target,EAIFocusPriority::Gameplay);
			SpawnArrow();
			MonsterAnim->IsAttack = true;
		}
	}
}

void URangerMonsterFSM::SpawnArrow()
{
	//UE_LOG()
	FTransform ShootPoint = Self->ArrowComp->GetComponentTransform();
	GetWorld()->SpawnActor<AMonsterArrowActor>(ArrowClass,ShootPoint);
	
}
