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
		// �÷��̾ �̵��� ���� ��ġ
		FVector HitPlace = FVector::ZeroVector; // �ʱ�ȭ
		// �浹�� ������Ʈ�� ������ ����
		UPrimitiveComponent* OverlappingComponents;
		// �浵���� ������Ʈ ������ ����
		OverlappingComponents = Cast<UPrimitiveComponent>(OtherActor);
		// ���� Ʈ���̽� ������ ���� �ʿ� - ���� ȭ���� �߰������� ���� 
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

		// �÷��̾ �̵��� ���� ��ġ
        FVector HitPlace = FVector::ZeroVector; // �ʱ�ȭ
		// �浹�� ������Ʈ�� ������ �迭
        TArray<UPrimitiveComponent*> OverlappingComponents;
		// �浵���� ������Ʈ �迭�� ����
        GetOverlappingComponents(OverlappingComponents);
		// ���� Ʈ���̽� ������ ���� �ʿ� - ���� ȭ���� �߰������� ���� 
		FVector StartLoc = TraceStartPoint->GetComponentLocation();
		FVector EndLoc = StartLoc + FVector(0, 0, -100);

		/*
		// ���� Ʈ���̽� ������ ���� �ʿ� - ���� ȭ���� �߰������� ���� 
		FVector StartLoc = GetActorLocation();
		*/


		for (UPrimitiveComponent* Component : OverlappingComponents) {
			FHitResult HitResult;
			if (Component->LineTraceComponent(HitResult, StartLoc, EndLoc, FCollisionQueryParams())) {// �ε����� �ݸ��� ä�� �����ʿ�
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
			// ����Ų ����(direction �������� SightRange �Ÿ���ŭ �߻��� ������ ���� ���� ����)���� 

		float sightRange;
		FVector direction; 
		FVector pivot;

		FHitResult hitInfo;
		FVector startVec = pivot;
		FVector endtVec = pivot + direction * sightRange;
		bool bIsCollide = GetWorld()->LineTraceSingleByChannel(hitInfo, startVec, endtVec, ECollisionChannel::ECC_Visibility);

		// ����, ��Ҵٸ� ���� �̵���Ų��. 
		if (bIsCollide) {

			//SetActorLocation(hitInfo.ImpactPoint + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

			// ��Ҵٸ� ���� �������� ������ �׸���. 
			DrawDebugLine(GetWorld(), startVec, hitInfo.ImpactPoint, FColor::Red);

		}
		// ���� �ʾҴٸ� �ִ� �������� ������ �׸���. 
		else {
			DrawDebugLine(GetWorld(), startVec, endtVec, FColor::Red);

		}

		//=============================================================
		// Black Fade In ȿ���� �ش�. 
		Player->GetController<APlayerController>()->PlayerCameraManager->StartCameraFade(0, 1.0f, TeleportDelay, FLinearColor::Black);

		if (!TargetLocation.IsNearlyZero()) {

			FTimerHandle TeleportTimer;

			GetWorld()->GetTimerManager().SetTimer(TeleportTimer, FTimerDelegate::CreateLambda([&]() {
				// 1. �÷��̾� �̵�
				Player->SetActorLocation(TargetLocation + FVector(0, 0, Player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

				// 2. �� ����Ʈ ǥ�� ����
				teleportRIngInst->Ring_FX->SetVisibility(false);
			
				// 3. ���� ����Ʈ�� �迭 �� �ʱ�ȭ
				TArray<FVector> resetVec = {FVector::ZeroVector, FVector::ZeroVector};

				UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(Player->teleportFX, FName("PointArray"), resetVec);

				}), TeleportDelay, false);
		}
		*/

    }


}
