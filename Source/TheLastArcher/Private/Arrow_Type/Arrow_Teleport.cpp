// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow_Type/Arrow_Teleport.h"
#include "Arrow_Base.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Actor.h>
#include "Player_Archer.h"
#include "WarpPlace.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>


AArrow_Teleport::AArrow_Teleport()
{
	
}

void AArrow_Teleport::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);



	// 부딧히는 대상 판정 수정 필요
	if (OtherActor->IsA<AWarpPlace>()) {
		/*
		// 지정한 장소로 플레이어 이동 - 위프 위치 수정 필요
		Player_Archer->SetActorLocation(FVector(0));


		FVector HitPlace = 
		*/
		/*

		//Player_Archer->SetActorLocation(FVector(0, 0, Player_Archer->GetDefaultHalfHeight()));


		FHitResult hitInfo;
		SetActorLocation(hitInfo.ImpactPoint + FVector(0, 0, Player_Archer->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

		SetActorLocation(hitInfo.ImpactPoint + FVector(0, 0, Player_Archer->GetDefaultHalfHeight()));
		*/

		//this->Destroy();
	}


	if (OtherActor->IsA<AWarpPlace>()) {

		UE_LOG(LogTemp, Warning, TEXT("Success Hit Warp"));

        FVector HitPlace = FVector::ZeroVector;
        TArray<UPrimitiveComponent*> OverlappingComponents;
        GetOverlappingComponents(OverlappingComponents);


        for (UPrimitiveComponent* Component : OverlappingComponents) {
            FHitResult HitResult;
            if (Component->LineTraceComponent(HitResult, GetActorLocation(), GetActorLocation() + FVector(0, 0, -100), FCollisionQueryParams())) {
                HitPlace = HitResult.ImpactPoint;
                break;
            }
        }

        if (HitPlace != FVector::ZeroVector) {
            Player_Archer->SetActorLocation(HitPlace);
        }

		
		//===========================================================
		/*
			// 가리킨 지점(direction 방향으로 SightRange 거리만큼 발사한 라인이 땅과 닿은 지점)으로 

		float sightRange;
		FVector direction; 
		FVector pivot;

		FHitResult hitInfo;
		FVector startVec = pivot;
		FVector endtVec = pivot + direction * sightRange;
		bool bIsCollide = GetWorld()->LineTraceSingleByChannel(hitInfo, startVec, endtVec, ECollisionChannel::ECC_Visibility);

		// 만일, 닿았다면 나를 이동시킨다. 
		if (bIsCollide) {

			//SetActorLocation(hitInfo.ImpactPoint + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

			// 닿았다면 닿은 지점까지 라인을 그린다. 
			DrawDebugLine(GetWorld(), startVec, hitInfo.ImpactPoint, FColor::Red);

		}
		// 닿지 않았다면 최대 지점까지 라인을 그린다. 
		else {
			DrawDebugLine(GetWorld(), startVec, endtVec, FColor::Red);

		}

		//=============================================================
		// Black Fade In 효과를 준다. 
		Player->GetController<APlayerController>()->PlayerCameraManager->StartCameraFade(0, 1.0f, TeleportDelay, FLinearColor::Black);

		if (!TargetLocation.IsNearlyZero()) {

			FTimerHandle TeleportTimer;

			GetWorld()->GetTimerManager().SetTimer(TeleportTimer, FTimerDelegate::CreateLambda([&]() {
				// 1. 플레이어 이동
				Player->SetActorLocation(TargetLocation + FVector(0, 0, Player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

				// 2. 링 이펙트 표시 끄기
				teleportRIngInst->Ring_FX->SetVisibility(false);
			
				// 3. 라인 이펙트의 배열 값 초기화
				TArray<FVector> resetVec = {FVector::ZeroVector, FVector::ZeroVector};

				UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(Player->teleportFX, FName("PointArray"), resetVec);

				}), TeleportDelay, false);
		}
		*/

        Destroy();
    }


}
