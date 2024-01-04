


#include "AI/BossMonster/BossSkullProjectile.h"

#include "Player_Archer.h"
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

	Target = Cast<APlayer_Archer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ABossSkullProjectile::OverlapBegin);
}


void ABossSkullProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void ABossSkullProjectile::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

