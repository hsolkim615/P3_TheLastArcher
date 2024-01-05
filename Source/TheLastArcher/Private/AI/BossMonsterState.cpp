


#include "AI/BossMonsterState.h"

#include "MonsterBase.h"
#include "AI/BossMonster/MonsterBoss.h"
#include "AI/BossMonster/MonsterBossFSM.h"


UBossMonsterState::UBossMonsterState()
{
	
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 1500;
	CurrentHealth = MaxHealth;
	
}



void UBossMonsterState::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UBossMonsterState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UBossMonsterState::UpdateHP(float UpdatedHealth)
{
	CurrentHealth = FMath::Max(0,CurrentHealth+UpdatedHealth);
}

void UBossMonsterState::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	UpdateHP(-Damage);
	AMonsterBoss* BossMon = Cast<AMonsterBoss>(DamagedActor);
	if(BossMon != nullptr)
	{
		if(CurrentHealth>Phase2)
		{
			BossMon->BossFsm->SetState(EBossMonsterState::Idle);
		}
		else if(CurrentHealth > 0 && CurrentHealth < Phase2) BossMon->BossFsm->SetState(EBossMonsterState::Phase2);
		else BossMon->BossFsm->SetState(EBossMonsterState::Died);
	}
}

