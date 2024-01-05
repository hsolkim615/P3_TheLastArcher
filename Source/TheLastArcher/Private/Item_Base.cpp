// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Base.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/StaticMesh.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Player_Archer.h"

// Sets default values
AItem_Base::AItem_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComp"));
	SetRootComponent(CollisionComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	
	




}

// Called when the game starts or when spawned
void AItem_Base::BeginPlay()
{
	Super::BeginPlay();

	Player_Archer = Cast<APlayer_Archer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

// Called every frame
void AItem_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

