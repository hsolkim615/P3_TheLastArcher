


#include "AI/BossMonster/MonsterBossFSM.h"

#include "AIController.h"
#include "Player_Archer.h"
#include "AI/BossMonsterAnim.h"
#include "AI/BossMonster/BossMonsterProjectile.h"
#include "AI/BossMonster/MonsterBoss.h"


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
	UE_LOG(LogTemp,Warning,TEXT("IDlE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"))
	SkillCoolTime += GetWorld()->GetDeltaSeconds();
	AI->SetFocus(Target,EAIFocusPriority::Gameplay);
	Target = Cast<APlayer_Archer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(Target != nullptr)
	{
		SetState(EBossMonsterState::Throw);
	}
	if(SkillCoolTime > SkillTime)
	{
		SetState(EBossMonsterState::SpawnSkull);
	}
}

void UMonsterBossFSM::TickThrow()
{
	CurrentTime += GetWorld()->GetDeltaSeconds();
	AI->SetFocus(Target,EAIFocusPriority::Gameplay);
	// 랜덤으로 공격시간을 준다.
	if(CurrentTime>AttackTime)
	{
		UE_LOG(LogTemp,Warning,TEXT("Spawn!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"))
		if (BossMonsterAnim->Montage_IsPlaying(BossMonsterAnim->Throw) == false)
		{
			Self->PlayAnimMontage(AM_BossAction,1.0f,FName("Throw"));
			CurrentTime = 0;
		}
		
		SetState(EBossMonsterState::Idle);
	}
	// 스킬킬로 전환.
	// 스킬 쿨타임은 10초로 고정.
}

void UMonsterBossFSM::TickSpawnSkull()
{
	
	// 해골을 보스 몬스터 주위에 소환하여 플레이어게 향하도록 날라간다.(모든 해골은 맞추면 없어진다.)
	UE_LOG(LogTemp,Warning,TEXT("SpawnSKull!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"))
	SkillCoolTime = 0;
	if(BossMonsterAnim->Montage_IsPlaying(BossMonsterAnim->Spawn) == false)
	{
		Self->PlayAnimMontage(AM_BossAction,1.0f,FName("Spawn"));
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
}

void UMonsterBossFSM::SpawnRock()
{
	FTransform ThrowPoint = Self->SpawnStone->GetComponentTransform();
	GetWorld()->SpawnActor<ABossMonsterProjectile>(PRJClass,ThrowPoint);
}

void UMonsterBossFSM::SpawnSkull()
{
	
}

void UMonsterBossFSM::OnThrowMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	
}


