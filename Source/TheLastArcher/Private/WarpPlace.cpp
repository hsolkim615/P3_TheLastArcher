// Fill out your copyright notice in the Description page of Project Settings.


#include "WarpPlace.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>

// Sets default values
AWarpPlace::AWarpPlace()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
	BoxCollision->SetRelativeScale3D(FVector(1, 1, 0.1f));




}

// Called when the game starts or when spawned
void AWarpPlace::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWarpPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

