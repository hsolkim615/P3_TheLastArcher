


#include "AI/BossMonster/MonsterBossFSM.h"

#include "AIController.h"
#include "MonsterBase.h"
#include "Player_Archer.h"
#include "AI/BossMonsterAnim.h"
#include "AI/MonsterFSM.h"
#include "AI/BossMonster/BossMonsterProjectile.h"
#include "AI/BossMonster/BossSkullProjectile.h"
#include "AI/BossMonster/MonsterBoss.h"
#include "AI/BossMonster/SpawnedSpell.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"


UMonsterBossFSM::UMonsterBossFSM()
{
	
	PrimaryComponentTick.bCanEverTick = true;

	
}



void UMonsterBossFSM::BeginPlay()
{
	Super::BeginPlay();

	// 주인 지정
	Self = Cast<AMonsterBoss>(GetOwner());
	AI = Cast<AAIController>(Self->GetController());
	
	BossMonsterAnim = Cast<UBossMonsterAnim>(Self->GetMesh()->GetAnimInstance());
	if(BossMonsterAnim != nullptr)
	{
		BossMonsterAnim -> OnMontageEnded.AddDynamic(this,&UMonsterBossFSM::OnThrowMontageEnded);
	}
	
	
	
}


// Called every frame
void UMonsterBossFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (State)
	{
	case EBossMonsterState :: Idle:		    TickIdle();		break;
	case EBossMonsterState :: Throw:	    TickThrow();		break;
	case EBossMonsterState :: SpawnSkull:   TickSpawnSkull(); break;
	case EBossMonsterState :: Phase2:		Tickphase2();	  break;
	case EBossMonsterState :: SpawnMonster: TickSpawnMonster(); break;
	case EBossMonsterState :: CastSpell:    TickCastSpell(); break;
	case EBossMonsterState :: Died:	        TickDied();		break;
	}
	
}

void UMonsterBossFSM::TickIdle()
{
	//UE_LOG(LogTemp,Warning,TEXT("IDlE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"))
	CurrentTime += GetWorld()->GetDeltaSeconds();
	AI->SetFocus(Target,EAIFocusPriority::Gameplay);
	Target = Cast<APlayer_Archer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(Target != nullptr && CurrentTime>AttackTime)
	{
		UE_LOG(LogTemp,Warning,TEXT("AttackTime!!!!!"));
		//30%확률로 스킬을 사용하도록한다.
		float RandomValue = FMath::FRand();
		if(RandomValue <= 0.3f)
		{
			UE_LOG(LogTemp,Warning,TEXT("Skill!!!!!"));
			SetState(EBossMonsterState::SpawnSkull);
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("JustAttack"));
			SetState(EBossMonsterState::Throw);
		}
	}
}


void UMonsterBossFSM::TickThrow()
{
	AI->SetFocus(Target,EAIFocusPriority::Gameplay);
	if (BossMonsterAnim->Montage_IsPlaying(BossMonsterAnim->Throw) == false)
	{
		//UE_LOG(LogTemp,Warning,TEXT("Spawn!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"))
			Self->PlayAnimMontage(AM_BossAction,1.0f,FName("Throw"));
			CurrentTime = 0;
	}
	SetState(EBossMonsterState::Idle);
}
	


void UMonsterBossFSM::TickSpawnSkull()
{
	
	
	// 해골을 보스 몬스터 주위에 소환하여 플레이어게 향하도록 날라간다.(모든 해골은 맞추면 없어진다.)
	CurrentTime = 0;
	if(BossMonsterAnim->Montage_IsPlaying(BossMonsterAnim->Spawn) == false)
	{
		Self->PlayAnimMontage(AM_BossAction,1.0f,FName("SpawnSkull"));
	}
	SetState(EBossMonsterState::Idle);
}

void UMonsterBossFSM::TickDied()
{
	// 죽으면 애니메이션 발동 후 사망.
	CurrentTime += GetWorld()->GetDeltaSeconds();
	if(CurrentTime > DieTime)
	{
		Self->PlayAnimMontage(AM_BossAction,1.0f,FName("Died"));
		Self->Destroy();	
	}
	
}

void UMonsterBossFSM::Tickphase2()
{
	Self->DamagePoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 시간이 흐르면 랜덤으로
	CurrentTime += GetWorld()->GetDeltaSeconds();
	if(CurrentTime > AttackTime)
	{
		float RandomValue = FMath::FRand();
		if(RandomValue<0.2f)
		{
			SetState(EBossMonsterState::SpawnMonster);
			
		}
		else
		{
			SetState(EBossMonsterState::CastSpell);
		}
	}
}

void UMonsterBossFSM::TickSpawnMonster()
{
	Self->DamagePoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 몬스터를 소환하는 동안 약점 콜리전을 꺼서 무적 상태로 만들고 몬스터를 다 잡으면 무적상태가 풀리게된다.
	//소환
	if(IsAllDead()==true)
	{
		// 콜리전을 몬스터 형태로 바꿔준다.
		// Self->WeekpointCapsuleComp->SetCollisionEnabled(ECollisionEnabled::);
	}
	// 무적 상태가 풀리면 시간을 초기화 하고, 다음 행동으로 넘어간다.
}

void UMonsterBossFSM::TickCastSpell()
{
	Self->DamagePoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Self->PlayAnimMontage(AM_BossAction,1.0f,FName("MonsterSpell"));
	// 마법을 캐스팅하는동안 특정 액터를 손에 만들고 그 액터를 부수지못하면 플레이어는 죽게만든다.
	// 부수게 되면 애니메이션이 작동하여 약점이 노출되게한다. 애니메이션이 끝나면 다음 행동으로 넘어간다.
}

void UMonsterBossFSM::SetState(EBossMonsterState Next)
{
	State = Next;
	CurrentTime = 0;
}

void UMonsterBossFSM::SpawnRock()
{
	UE_LOG(LogTemp,Warning,TEXT("SpawnRock!!!!!!!!!!!!!!!!!!!!!!"))
	FTransform ThrowPoint = Self->SpawnStone->GetComponentTransform();
	GetWorld()->SpawnActor<ABossMonsterProjectile>(PRJClass,ThrowPoint);
}

void UMonsterBossFSM::SpawnSkull()
{
	UE_LOG(LogTemp,Warning,TEXT("Skill888888888888888888888888"))

	SpawnTime = GetWorld()->GetDeltaSeconds();

	FTransform SpawnPoint1 = Self->SkullSpawn1->GetComponentTransform();
	FTransform SpawnPoint2 = Self->SkullSpawn2->GetComponentTransform();
	FTransform SpawnPoint3 = Self->SkullSpawn3->GetComponentTransform();

	GetWorld()->SpawnActor<ABossSkullProjectile>(SkullClass,SpawnPoint1);
	UE_LOG(LogTemp,Warning,TEXT("Spawn11111111111111111111111111111"))

	if(SpawnTime > FixedSpawnTime)
	{
		GetWorld()->SpawnActor<ABossSkullProjectile>(SkullClass,SpawnPoint2);
		UE_LOG(LogTemp,Warning,TEXT("Spawn22222222222222222222222222222222"))
	}
	else
	{
		GetWorld()->SpawnActor<ABossSkullProjectile>(SkullClass,SpawnPoint3);
		UE_LOG(LogTemp,Warning,TEXT("Spawn333333333333333333333333333333"))
		SpawnTime = 0;
	}
	

}

void UMonsterBossFSM::SpawnSpell()
{
	FTransform SpawnSpellLoc = Self->SpawnSpellpoint->GetComponentTransform();
	GetWorld()->SpawnActor<ASpawnedSpell>(SpellClass,SpawnSpellLoc);
}

void UMonsterBossFSM::OnThrowMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	
}

// 죽었는지 확인하는 함수.
bool UMonsterBossFSM::IsAllDead()
{
	// 배열안에 있는 몬스터들을 확인하여
	for(AMonsterBase* SummonedMonster:SummonedMonsters)
	{
		//죽은게 아니라면
		if(SummonedMonster && !SummonedMonster->MonsterFsm->IsDead())
		{
			// false반환
			return false;
		}
	}
	// 다죽으면 true반환
	return true;
}


