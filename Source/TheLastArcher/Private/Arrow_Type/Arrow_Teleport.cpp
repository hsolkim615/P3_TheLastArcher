// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow_Type/Arrow_Teleport.h"
#include "Arrow_Base.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Actor.h>
#include "Player_Archer.h"
#include "WarpPlace.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/PrimitiveComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Public/CollisionQueryParams.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/EngineTypes.h>
#include "Components/CapsuleComponent.h"


AArrow_Teleport::AArrow_Teleport()
{
	




	// 라인 시작 위치를 static메쉬로 설정
	TraceStartPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TraceStartPoint"));
	TraceStartPoint->SetupAttachment(RootComponent);
	//TraceStartPoint->SetRelativeLocation(FVector(-0.44f, 0.8f, -40.5f)); 
	TraceStartPoint->SetRelativeLocation(FVector(-18, 13, -32)); // (X=-18.000000,Y=13.000000,Z=-32.000000)

}

void AArrow_Teleport::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && OtherActor->IsA<AWarpPlace>()) {

		UE_LOG(LogTemp, Warning, TEXT("Success Hit Warp"));

		// 플레이어가 이동할 최종 위치
		FVector HitPlace = FVector::ZeroVector; // 초기화
		// 충돌한 컴포넌트를 저장할 배열
		TArray<UPrimitiveComponent*> OverlappingComponents;
		// 충도돌한 컴포넌트 배열에 저장
		GetOverlappingComponents(OverlappingComponents);
		// 라인 트레이스 시작점  
		FVector StartLoc = TraceStartPoint->GetComponentLocation();
		// 라인 트레이스 시작점  
		FVector EndLoc = StartLoc + FVector(0, 0, -100);
		// 시작점에서 도착점으로 라인이 나가는 동안, 부딪힌 액터가 있을 것

		//FCollisionQueryParams TraceParams(FName(TEXT("MyTrace")), false);
		FCollisionObjectQueryParams ObjectParams;
		// WarpPlace콜리전 채널만 감지하도록 함
		ObjectParams.AddObjectTypesToQuery(ECC_GameTraceChannel9);

		// OverlappingComponents의 크기만큼 반복 - 아마 1일 것
		for (UPrimitiveComponent* Component : OverlappingComponents) {
			// 부딪힌 결과 값
			FHitResult HitResult;
			// 라인이 부딪힌 경우
			if (GetWorld()->LineTraceSingleByObjectType(HitResult, StartLoc, EndLoc, ObjectParams, FCollisionQueryParams())) {// 부딪히는 콜리전 채널 점검필요
				// 라인이 부딪힌 위치를 저장
				HitPlace = HitResult.ImpactPoint;

				break;
			}
		}

		if (HitPlace != FVector::ZeroVector) {
			// 저장된 위치 값으로 플레이어 이동
			Player_Archer->SetActorLocation(HitPlace);
		}
		
		Destroy();


		// 문제1 - 라인이 시작하는 위치로 GetComponentLocation()를 하였으나, 이는 화살의 중심점이므로, 그곳에서 화살을 쏘면 플레이어가 화살이 부딪힌 위치보다 조금 뒤로 이동하게 됨. 그러니 라인의 시작 위치를 화살촉의 부분이 되도록 조정할 필요가 있음 = 해결
		
		// 문제2 - 플레이어의 위치 이동이 안됨 -> 라인의 길이가 콜리전의 영역 밖으로 나갈정도의 길이가 되어야 함. 그렇지 않으면 콜리전이 부딪혔을 때, 라인은 아무 액터에도 부딪히지 못하고 위치값을 가져오지 못함. 위치 값이 없으면 플레이어는 이동을 못함
			// 또는 화살을 감싸는 콜리전의 크기 자체를 줄여볼 수도 있음
			// 마약 라인의 길이가 너무 길면 너무 일찍 라인이 나가면, 보이는 것보다 일찍 라인이 충돌해서 플레이어가 의도한 것보다 뒤쪽으로 이동할 수 있음



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
