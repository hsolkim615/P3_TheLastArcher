


#include "AI/BossMonster/BossSkullProjectile.h"

#include "Player_Archer.h"
#include "Player_DamageType.h"
#include "StatesComponent.h"
#include "AI/BossMonster/MonsterBoss.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ABossSkullProjectile::ABossSkullProjectile()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SetRootComponent(SphereComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(SphereComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Resource/BossWP/Skull/Skull.Skull'"));
	if(TempMesh.Succeeded())
	{
		MeshComp->SetStaticMesh(TempMesh.Object);
	}
	
}


void ABossSkullProjectile::BeginPlay()
{
	Super::BeginPlay();

	// 타이머를 사용하여 0.1초마다 Target을 찾도록하였다.
	GetWorldTimerManager().SetTimer(TimerHandle_FindTarget, this, &ABossSkullProjectile::FindTarget, 0.1f, true);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ABossSkullProjectile::OverlapBegin);
}


void ABossSkullProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 살아가는동안
	// 타겟의 방향을 정해서 향하도록할것이다.
	if(Target)
	{
		FVector Direction = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		SetActorRotation(Direction.Rotation());
		// 위치로 이동시킬것이다.
		FVector NewLocation = GetActorLocation() + Direction * Speed * DeltaTime;
		SetActorLocation(NewLocation);
	}
	


}


void ABossSkullProjectile::FindTarget()
{
	// 타이머에 호출 될 타겟을 플레이어로 정해주는 함수를 만든다.
	Target = Cast<APlayer_Archer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
}

void ABossSkullProjectile::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 부딪힌 대상을 플레이어인지 체크
	if(OtherActor -> IsA<APlayer_Archer>())
	{
		// 부딪힌 대상이 플레이어라면 스텟 컴퍼넌트로 들어가서 대미지를 준다.
		auto Player = Cast<APlayer_Archer>(OtherActor);
		Player->StatesComp->TakeDamage(Player,Damage,NormalDamage,nullptr,this);
		
	}
}

