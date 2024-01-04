// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BossMonster/BossMonsterProjectile.h"

#include "Player_Archer.h"
#include "AI/BossMonster/MonsterBoss.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnitConversion.h"

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
	
}

// Called when the game starts or when spawned
void ABossMonsterProjectile::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<APlayer_Archer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto Temp = UGameplayStatics::GetActorOfClass(GetWorld(), 
			AMonsterBoss::StaticClass());
	Self = Cast<AMonsterBoss>(Temp);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ABossMonsterProjectile::OverlapBegin);
	
	
}

// Called every frame
void ABossMonsterProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Target!= nullptr)
	{

		FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
		Direction.Normalize();
		FVector Velocity = Direction * Speed;
		SetActorLocation(GetActorLocation()+Velocity*DeltaTime);
		
	}
	
	
}

void ABossMonsterProjectile::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

