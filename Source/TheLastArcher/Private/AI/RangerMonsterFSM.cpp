// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RangerMonsterFSM.h"

#include "MonsterBase.h"
#include "AI/MonsterAnim.h"

// void UMonsterFSM::TickAttack()
// {
// 	if(CurrentTime > AttackTime)
// 	{
// 		MonsterAnim->IsAttack = true;
// 		CurrentTime = 0;
// 		float Dist = FVector::Dist(Self->GetActorLocation(),Target->GetActorLocation());
// 		if(Dist>AttackRange)
// 		{
// 			SetState(EMonsterState::Move);
// 			MonsterAnim->IsAttack = false;
// 		}
// 		else
// 		{
// 			
// 		}
// 	}
// }
//
// void URangerMonsterFSM::SpawnArrow()
// {
// 	
// }
