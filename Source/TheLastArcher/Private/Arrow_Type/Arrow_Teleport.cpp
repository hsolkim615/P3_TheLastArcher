// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow_Type/Arrow_Teleport.h"
#include "Arrow_Base.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Actor.h>
#include "Player_Archer.h"
#include "WarpPlace.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/PrimitiveComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>


AArrow_Teleport::AArrow_Teleport()
{
	TraceStartPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TraceStartPoint"));
	TraceStartPoint->SetupAttachment(RootComponent);
	TraceStartPoint->SetRelativeLocation(FVector(-0.44f, 0.8f, -40.5f));

}

void AArrow_Teleport::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && OtherActor->IsA<AWarpPlace>()) {

		UE_LOG(LogTemp, Warning, TEXT("Success Hit Warp"));

		/*
		// 플레이어가 이동할 최종 위치
		FVector HitPlace = FVector::ZeroVector; // 초기화
		// 충돌한 컴포넌트를 저장할 변수
		UPrimitiveComponent* OverlappingComponents;
		// 충도돌한 컴포넌트 변수에 저장
		OverlappingComponents = Cast<UPrimitiveComponent>(OtherActor);
		// 라인 트레이스 시작점 수정 필요 - 현재 화살의 중간점부터 나감 
		FVector StartLoc = GetActorLocation();


		if (OverlappingComponents) {
			FHitResult HitResult;
			if (OverlappingComponents->LineTraceComponent(HitResult, StartLoc, GetActorLocation() + FVector(0, 0, -100), FCollisionQueryParams())) {
				HitPlace = HitResult.ImpactPoint;
			}

			if (HitPlace != FVector::ZeroVector) {
				Player_Archer->SetActorLocation(HitPlace);
			}
		}
		
		Destroy();
		*/



		//===========================================================

		// 플레이어가 이동할 최종 위치
        FVector HitPlace = FVector::ZeroVector; // 초기화
		// 충돌한 컴포넌트를 저장할 배열
        TArray<UPrimitiveComponent*> OverlappingComponents;
		// 충도돌한 컴포넌트 배열에 저장
        GetOverlappingComponents(OverlappingComponents);
		// 라인 트레이스 시작점 수정 필요 - 현재 화살의 중간점부터 나감 
		FVector StartLoc = TraceStartPoint->GetComponentLocation();
		FVector EndLoc = StartLoc + FVector(0, 0, -100);

		/*
		// 라인 트레이스 시작점 수정 필요 - 현재 화살의 중간점부터 나감 
		FVector StartLoc = GetActorLocation();
		*/


		for (UPrimitiveComponent* Component : OverlappingComponents) {
			FHitResult HitResult;
			if (Component->LineTraceComponent(HitResult, StartLoc, EndLoc, FCollisionQueryParams())) {// 부딪히는 콜리전 채널 점검필요
				HitPlace = HitResult.ImpactPoint;



				break;
			}
		}

		if (HitPlace != FVector::ZeroVector) {
			Player_Archer->SetActorLocation(HitPlace);
		}

		Destroy();

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

    }


}
