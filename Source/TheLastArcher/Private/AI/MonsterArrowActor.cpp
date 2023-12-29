// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MonsterArrowActor.h"

#include <Engine/DamageEvents.h>

#include "AI/MonsterFSM.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "StatesComponent.h"


// Sets default values
AMonsterArrowActor::AMonsterArrowActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComp");
	CapsuleComp -> SetupAttachment(RootComponent);
	
	

	Arrow = CreateDefaultSubobject<UStaticMeshComponent>("Arrow");
	Arrow -> SetupAttachment(CapsuleComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	ProjectileMovementComp -> InitialSpeed = 1000;
	ProjectileMovementComp -> MaxSpeed = 1000;
}


void AMonsterArrowActor::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AMonsterArrowActor::OverlapBegin);
	
}


void AMonsterArrowActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//P=P0+Vt;
	float Velocity = Speed * GetWorld()->GetDeltaSeconds();
	SetActorLocation(GetActorLocation()+GetActorForwardVector()*Velocity);
	
}

void AMonsterArrowActor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                      bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor != Cast<APlayer_Archer>(OtherActor))
	{
		if(OtherActor &&(OtherActor != this) && OtherComp)
		{
			OtherActor->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
		}
	}
	
}
