

#include "AI/BossMonster/SpawnedSpell.h"

#include "Arrow_Base.h"
#include "Player_Archer.h"
#include "Player_DamageType.h"
#include "StatesComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"




ASpawnedSpell::ASpawnedSpell()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CapusleComp = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComp");
	
	// MeshComp->CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
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
	CapusleComp->OnComponentBeginOverlap.AddDynamic(this,&ASpawnedSpell::OverlapBegin);
	CurrentTime += GetWorld()->GetDeltaSeconds();
	if(CurrentTime>CastTime)
	{
		if(Target != nullptr)
		{
			Target->StatesComp->TakeDamage(Target,Damag,NormalDamage,nullptr,this);
			CurrentTime = 0;
			this->Destroy();
		}
		
	}
}


void ASpawnedSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 3방 맞으면 부서짐
	if(Count>MaxCount)
	{
		this->Destroy();
	}

}




void ASpawnedSpell::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//부딪힌 대상이 화살인지 체크
	auto Arrow = Cast<AArrow_Base>(OtherActor);
	if(Arrow != nullptr)
	{
		Count ++;
	}
	
}

