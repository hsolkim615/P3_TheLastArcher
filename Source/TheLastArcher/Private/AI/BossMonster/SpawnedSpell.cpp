

#include "AI/BossMonster/SpawnedSpell.h"

#include "Arrow_Base.h"
#include "Player_Archer.h"
#include "Player_DamageType.h"
#include "StatesComponent.h"
#include "AI/BossMonster/MonsterBoss.h"
#include "AI/BossMonster/MonsterBossFSM.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"




ASpawnedSpell::ASpawnedSpell()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("CapsuleComp");
	SphereComp -> SetupAttachment(RootComponent);
	
	// MeshComp->CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	// MeshComp->SetupAttachment(CapusleComp);
	// ConstructorHelpers::FObjectFinder<UStaticMesh>TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Resource/BossWP/Mine/Crystal_Crystal_007_low.Crystal_Crystal_007_low'"));
	// if(TempMesh.Succeeded())
	// {
	// 	MeshComp->SetStaticMesh(TempMesh.Object);
	// 	MeshComp->SetRelativeLocation(FVector(30,-30,-10));
	// 	MeshComp->SetRelativeScale3D(FVector(2.0f));
	// }
	
	
}


void ASpawnedSpell::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<APlayer_Archer>(GetWorld()->GetFirstPlayerController()->GetPawn());

	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ASpawnedSpell::OverlapBegin);
	
}


void ASpawnedSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime += GetWorld()->GetDeltaSeconds();
	
	if(CurrentTime>CastTime)
	{
		this->Destroy();
		if(Target != nullptr)
		{
			Target->StatesComp->TakeDamage(Target,Damag,NormalDamage,nullptr,this);
			
		}
		
	}

	// 3방 맞으면 부서짐
	if(Count>MaxCount)
	{
		Time += DeltaTime;
		this->Destroy();
		if(Boss != nullptr)
		{
			Boss->PlayAnimMontage(Boss->BossFsm->AM_BossAction,0.3f,TEXT("Week"));
			if(Time > WeekTime)
			{
				Boss->BossFsm->SetState(EBossMonsterState::Phase2);
			}
			
		}
		
	}

}




void ASpawnedSpell::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//부딪힌 대상이 화살인지 체크
	UE_LOG(LogTemp,Warning,TEXT("overlaped!!!!!!!!!"));
	auto Arrow = Cast<AArrow_Base>(OtherActor);
	if(Arrow != nullptr)
	{
		Count ++;
	}
	
}

