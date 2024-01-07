


#include "AI/BossMonster/BoassSpellActor.h"

#include "Components/CapsuleComponent.h"


ABoassSpellActor::ABoassSpellActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	
}


void ABoassSpellActor::BeginPlay()
{
	Super::BeginPlay();
	CapsulComp ->OnComponentBeginOverlap.AddDynamic(this,&ABoassSpellActor::OverlapBegin);
}


void ABoassSpellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoassSpellActor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

