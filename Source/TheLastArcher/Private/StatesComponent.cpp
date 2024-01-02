


#include "StatesComponent.h"

#include "AIController.h"
#include "InterchangeResult.h"
#include "MonsterBase.h"
#include "AI/MonsterFSM.h"


UStatesComponent::UStatesComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100;
	CurrentHealth = MaxHealth;
	UpdateHP(MaxHealth);

	
}


// Called when the game starts
void UStatesComponent::BeginPlay()
{
	Super::BeginPlay();

	// 컴포넌트이기때문에 사용자를 부여하기 위하여 Owner를 만들어준다.
	AActor* Owner = GetOwner();
	// 만약 제대로 들어갔다면
	if(Owner)
	{
		// 데미지 받는 함수를 바인딩하자.(델리게이트)
		// 호출되면 함수 실행이된다.
		Owner->OnTakeAnyDamage.AddDynamic(this,&UStatesComponent::TakeDamage);
		
	}
	
}

void UStatesComponent::UpdateHP(float UpdatedHealth)
{
	CurrentHealth = FMath::Max(0,CurrentHealth+UpdatedHealth);
	
}

// void UStatesComponent::TakeDamage(AActor* DamagedActor, float Damage)
// {
// 	UpdateHP(-Damage);
//
// 	if(DamagedActor -> IsA<AMonsterBase>())
// 	{
// 		AMonsterBase* Monster =Cast<AMonsterBase>(DamagedActor);
// 		if(CurrentHealth > 0)
// 		{
// 			UE_LOG(LogTemp,Warning,TEXT("MonsterHIt@@@@@@@@@@@@@@@@@@@@@@@@@@"))
// 			Monster->MonsterFsm->SetState(EMonsterState::Damage);
// 			Monster->MonsterFsm->PlayMontageHit();
// 		}
// 		else
// 		{
// 			Monster->MonsterFsm->SetState(EMonsterState::Die);
// 			Monster->MonsterFsm->PlayMontageDie();
// 		}
// 	}
// 	if(DamagedActor->IsA<APlayer_Archer>())
// 	{
// 		UE_LOG(LogTemp,Warning,TEXT("PlayerHIt222222222222222222222222222222"));
// 		// 플레이어
// 		UE_LOG(LogTemp,Warning,TEXT("PlayerHIt11111111111111111111111111111"));
// 	}
// }


void UStatesComponent::TakeDamage( AActor* DamagedActor, float Damage,
                                   const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	
	// 데미지가 음수 값이면 반영하지말고3
	if(Damage <= 0)
	{
		return;
	}
	// 데미지가 들어오면 CurrentHealth에서 데미지 값을 빼라.
	//CurrentHealth = FMath::Clamp(CurrentHealth-Damage,0.0f,MaxHealth);

	// 업데이트 함수 활용
	UpdateHP(-Damage);

	UE_LOG(LogTemp,Warning,TEXT("Damaged!"));
	// 함수가 호출되었을때 맞은 대상이 몬스터인지 확인
	if(DamagedActor->IsA<AMonsterBase>())
	{
		AMonsterBase* Monster = Cast<AMonsterBase>(DamagedActor);
		// 대상이 몬스터인데 현제 체력이 0 보다 크면 살아있으므로
		if(CurrentHealth > 0)
		{
			Monster->MonsterFsm->Ai->StopMovement();
			// 데미지 받은 상태로 전환
			Monster->MonsterFsm->SetState(EMonsterState::Damage);
			Monster->MonsterFsm->PlayMontageHit();
		}
		// 현제 체력이 0이하 이면 죽은 것이므로
		else
		{
			// 상태를 죽음으로 전환
			UE_LOG(LogTemp,Warning,TEXT("MonsterDied"));
			Monster->MonsterFsm->SetState(EMonsterState::Die);
			Monster->MonsterFsm->PlayMontageDie();
		}	
	}
	else
	{
		//플레이어
		UE_LOG(LogTemp,Warning,TEXT("PlayerHit111111111111111111111111111111111111"));
		//
		if(CurrentHealth>0)
		{
			//UI 감소
		}
		// 죽으면
		else
		{
			// 레벨 재시작
		}
	}
	
}











