


#include "AI/BossMonsterAnim.h"

#include "AI/BossMonster/MonsterBoss.h"
#include "AI/BossMonster/MonsterBossFSM.h"


void UBossMonsterAnim::AnimNotify_Throw()
{
	auto Boss = Cast<AMonsterBoss>(TryGetPawnOwner());
	if(Boss != nullptr)
	{
		Boss->BossFsm->SpawnRock();
	}
}

void UBossMonsterAnim::AnimNotify_SpawnSkull()
{
	auto Boss = Cast<AMonsterBoss>(TryGetPawnOwner());
	if(Boss != nullptr)
	{
		// Boss->BossFsm
	}
}
