// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MonsterArrowActor.h"

#include <Engine/DamageEvents.h>

#include "Player_DamageType.h"
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
	CapsuleComp->SetupAttachment(RootComponent);


	Arrow = CreateDefaultSubobject<UStaticMeshComponent>("Arrow");
	Arrow->SetupAttachment(CapsuleComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	ProjectileMovementComp->InitialSpeed = 5000;
	ProjectileMovementComp->MaxSpeed = 5000;
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
	// float Velocity = Speed * GetWorld()->GetDeltaSeconds();
	// SetActorLocation(GetActorLocation() + GetActorForwardVector() * Velocity);
}

void AMonsterArrowActor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                      bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("11111111111111111111111!"));
	{
		if (OtherComp->IsA<AMonsterArrowActor>())
		{
			auto* Target = Cast<UStatesComponent>(OtherActor);
			//Target->TakeDamage(Damage,,nullptr,this);
		}

	}
}
