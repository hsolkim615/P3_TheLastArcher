


#include "AI/BossMonsterState.h"

#include "MonsterBase.h"
#include "AI/BossMonster/MonsterBoss.h"
#include "AI/BossMonster/MonsterBossFSM.h"


UBossMonsterState::UBossMonsterState()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 1500;
	CurrentHealth = MaxHealth;
	
}



void UBossMonsterState::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if(Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this,&UBossMonsterState::TakeDamage);
	}
	
	
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
	// 데미지가 달면서
	UpdateHP(-Damage);
	AMonsterBoss* BossMon = Cast<AMonsterBoss>(DamagedActor);
	if(BossMon != nullptr)
	{
		// 현재 체력이 2페이지 기준치보다 높으면 Idle 상태로 전이.
		if(CurrentHealth>Phase2)
		{
			BossMon->BossFsm->SetState(EBossMonsterState::Idle);
		}
		// 현재 체력이 2페이지 기준치보다 밑으로 떨어지면 Phase2상태로 돌입.
		else
		{
			if(CurrentHealth<Phase2 && CurrentHealth>0)
			BossMon->BossFsm->SetState(EBossMonsterState::Phase2);
			// 현제 체력이 0 이하일 때 죽음 형태돌 돌입.
			else
			{
				//BossMon->BossFsm->SetState(EBossMonsterState::Died);
			}
		}
		
	}
}

