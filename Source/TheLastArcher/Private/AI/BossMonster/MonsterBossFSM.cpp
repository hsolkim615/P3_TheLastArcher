


#include "AI/BossMonster/MonsterBossFSM.h"

#include "AIController.h"
#include "Player_Archer.h"
#include "AI/BossMonsterAnim.h"
#include "AI/BossMonster/BossMonsterProjectile.h"
#include "AI/BossMonster/BossSkullProjectile.h"
#include "AI/BossMonster/MonsterBoss.h"
#include "Components/ArrowComponent.h"


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
	case EBossMonsterState :: Idle:		  TickIdle();		break;
	case EBossMonsterState :: Throw:	  TickThrow();		break;
	case EBossMonsterState :: SpawnSkull: TickSpawnSkull(); break;
	case EBossMonsterState :: Died:	      TickDied();		break;
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

void UMonsterBossFSM::OnThrowMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	
}


