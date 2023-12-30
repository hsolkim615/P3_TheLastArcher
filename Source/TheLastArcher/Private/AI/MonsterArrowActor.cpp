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
	Arrow->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	ProjectileMovementComp->InitialSpeed = 8000;
	ProjectileMovementComp->MaxSpeed = 8000;
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
		if(OtherActor->IsA<APlayer_Archer>())
		{
			UE_LOG(LogTemp,Warning,TEXT("22222222222222222222222222!"));
			auto Target = Cast<APlayer_Archer>(OtherActor);
			UE_LOG(LogTemp,Warning,TEXT("Hit231321321313212131231231231231232131"));
			Target->StatesComp->TakeDamage(Target,Damage,NomalDamge,nullptr,this);
			this->Destroy();
		}
		
	}
}
