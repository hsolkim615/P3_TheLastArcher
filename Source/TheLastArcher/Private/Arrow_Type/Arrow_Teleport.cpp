// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow_Type/Arrow_Teleport.h"
#include "Arrow_Base.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Actor.h>
#include "Player_Archer.h"
#include "WarpPlace.h"


AArrow_Teleport::AArrow_Teleport()
{
	
}

void AArrow_Teleport::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);



	// �ε����� ��� ���� ���� �ʿ�
	if (OtherActor->IsA<AWarpPlace>()) {
		
		// ������ ��ҷ� �÷��̾� �̵� - ���� ��ġ ���� �ʿ�
		Player_Archer->SetActorLocation(FVector(0));

		//GetWorld()->



		/*

		//Player_Archer->SetActorLocation(FVector(0, 0, Player_Archer->GetDefaultHalfHeight()));


		FHitResult hitInfo;
		SetActorLocation(hitInfo.ImpactPoint + FVector(0, 0, Player_Archer->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

		SetActorLocation(hitInfo.ImpactPoint + FVector(0, 0, Player_Archer->GetDefaultHalfHeight()));
		*/

		this->Destroy();
	}

}
