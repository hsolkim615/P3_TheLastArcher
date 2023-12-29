// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow_Base.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AArrow_Base::AArrow_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Arrow의 collision 생성
	ArrowCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ArrowCollisionComp"));
	SetRootComponent(ArrowCollisionComp);
	ArrowCollisionComp->SetRelativeScale3D(FVector(1, 0.4, 1));

	// Arrow의 외형
	ArrowMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMeshComp"));
	ArrowMeshComp->SetupAttachment(ArrowCollisionComp);
	ArrowMeshComp->SetRelativeLocation(FVector(0.4, 0, -0.4));
	ArrowMeshComp->SetWorldRotation(FRotator(-44, -25, 18));
	ArrowMeshComp->SetRelativeScale3D(FVector(3));
	//ArrowMeshComp->SetRelativeScale3D(FVector(2));S

	ConstructorHelpers::FObjectFinder<UStaticMesh>ArrowMesh(TEXT("/Script/Engine.StaticMesh'/Game/Resource/Arrow/WoodenArrow.WoodenArrow'"));

	if (ArrowMesh.Succeeded()) {
		ArrowMeshComp->SetStaticMesh(ArrowMesh.Object);

	}


}

// Called when the game starts or when spawned
void AArrow_Base::BeginPlay()
{
	Super::BeginPlay();

	

}

// Called every frame
void AArrow_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsShotArrow == true) {

		// ArrowGoingDirection의 방향으로 화살이 날아가도록 함
		this->SetActorLocation(GetActorLocation() + ArrowGoingDirection * ArrowSpeed * DeltaTime);

	}
}

void AArrow_Base::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
}

