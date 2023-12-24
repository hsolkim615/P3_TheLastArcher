// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBow.h"

// Sets default values
APlayerBow::APlayerBow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BowSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BowSkeletalMesh"));
	SetRootComponent(BowSkeletalMesh);

	ConstructorHelpers::FObjectFinder<USkeletalMesh>BowMeshComp(TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/Bow/uploads_files_3856554_bow.uploads_files_3856554_bow'"));

	if (BowMeshComp.Succeeded()) {
		BowSkeletalMesh->SetSkeletalMesh(BowMeshComp.Object);

	}



}

// Called when the game starts or when spawned
void APlayerBow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerBow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

