// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow_Base.h"

// Sets default values
AArrow_Base::AArrow_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ArrowMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMeshComp"));
	ArrowMeshComp->SetRelativeScale3D(FVector(2));

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

		SetActorLocation(GetActorLocation() + ArrowGoingDirection * ArrowSpeed * DeltaTime);

	}
}

