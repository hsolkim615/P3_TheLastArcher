// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/IT_HealPotion.h"
#include "Player_Archer.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "StatesComponent.h"

AIT_HealPotion::AIT_HealPotion()
{
	
	MeshComp->SetRelativeLocation(FVector(0, 0, -25));
	MeshComp->SetRelativeScale3D(FVector(2.5f));

	ConstructorHelpers::FObjectFinder<UStaticMesh>HealPotion(TEXT("/Script/Engine.StaticMesh'/Game/Resource/Item/HealPotion/MTR_IT_HealPotion.MTR_IT_HealPotion'"));
	
	if (HealPotion.Succeeded()) {
		MeshComp->SetStaticMesh(HealPotion.Object);
	}

}

void AIT_HealPotion::BeginPlay()
{
	Player_Archer = Cast<APlayer_Archer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

void AIT_HealPotion::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA<APlayer_Archer>()) {

		UE_LOG(LogTemp, Warning, TEXT("Get Heal Item"));

		Player_Archer->StatesComp->CurrentHealth += 30.f;

		this->Destroy();
	}
}
