


#include "AI/BossMonsterAnim.h"

#include "AI/BossMonster/MonsterBoss.h"
#include "AI/BossMonster/MonsterBossFSM.h"


void UBossMonsterAnim::AnimNotify_Throw()
{
	AMonsterBoss* Boss = Cast<AMonsterBoss>(TryGetPawnOwner());
	if(Boss != nullptr)
	{
		Boss->BossFsm->SpawnRock();
	}
}

void UBossMonsterAnim::AnimNotify_Spawn()
{
	auto Boss = Cast<AMonsterBoss>(TryGetPawnOwner());
	if(Boss != nullptr)
	{
		Boss->BossFsm->SpawnSkull();
	}
}
