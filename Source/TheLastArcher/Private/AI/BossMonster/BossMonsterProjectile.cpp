// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BossMonster/BossMonsterProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABossMonsterProjectile::ABossMonsterProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp -> SetupAttachment(RootComponent);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp -> SetupAttachment(SphereComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Resource/BossWP/Rock/Sand_Rock_vd5scco/Rock.Rock'"));
	if(TempMesh.Succeeded())
	{
		MeshComp->SetStaticMesh(TempMesh.Object);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MeshComp->SetRelativeScale3D(FVector(0.1f));
	}

	// PRJComp = CreateDefaultSubobject<UProjectileMovementComponent>("PRJComp");
	// PRJComp ->InitialSpeed = 1000.f;
	// PRJComp -> MaxSpeed = 1000.f;
	
}

// Called when the game starts or when spawned
void ABossMonsterProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ABossMonsterProjectile::OverlapBegin);
}

// Called every frame
void ABossMonsterProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//

	FVector Direction = GetActorForwardVector() * Speed;
	SetActorLocation(GetActorLocation()+Direction * DeltaTime);
}

void ABossMonsterProjectile::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

