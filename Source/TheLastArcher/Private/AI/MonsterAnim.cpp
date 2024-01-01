// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MonsterAnim.h"

#include "MonsterBase.h"

void UMonsterAnim::OnDamageEnd()
{
	AMonsterBase* Monster = Cast<AMonsterBase>(TryGetPawnOwner());
	if(Monster)
	{
		// 데미지 받으면 이동하는 몽타주 실행
		Monster->MonsterFsm->OnchangeMoveState();
	}
}

void UMonsterAnim::AnimNotify_DamageEnd()
{
	AMonsterBase* Monster = Cast<AMonsterBase>(TryGetPawnOwner());
	if(Monster)
	{
		Monster->MonsterFsm->OnchangeMoveState();
	}
	// 몽타주 스탑
	Montage_Stop(0.1f,Monster->MonsterFsm-> MonsterMontage);
}

void UMonsterAnim::AnimNotify_DieEnd()
{
	// 죽는 애니메이션 종료되면 ISDieDone을 true로 바꾼다.
	IsDieDone = true;
	
}

