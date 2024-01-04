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
	




	// ���� ���� ��ġ�� static�޽��� ����
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

		// �÷��̾ �̵��� ���� ��ġ
		FVector HitPlace = FVector::ZeroVector; // �ʱ�ȭ
		// �浹�� ������Ʈ�� ������ �迭
		TArray<UPrimitiveComponent*> OverlappingComponents;
		// �浵���� ������Ʈ �迭�� ����
		GetOverlappingComponents(OverlappingComponents);
		// ���� Ʈ���̽� ������  
		FVector StartLoc = TraceStartPoint->GetComponentLocation();
		// ���� Ʈ���̽� ������  
		FVector EndLoc = StartLoc + FVector(0, 0, -100);
		// ���������� ���������� ������ ������ ����, �ε��� ���Ͱ� ���� ��

		//FCollisionQueryParams TraceParams(FName(TEXT("MyTrace")), false);
		FCollisionObjectQueryParams ObjectParams;
		// WarpPlace�ݸ��� ä�θ� �����ϵ��� ��
		ObjectParams.AddObjectTypesToQuery(ECC_GameTraceChannel9);

		// OverlappingComponents�� ũ�⸸ŭ �ݺ� - �Ƹ� 1�� ��
		for (UPrimitiveComponent* Component : OverlappingComponents) {
			// �ε��� ��� ��
			FHitResult HitResult;
			// ������ �ε��� ���
			if (GetWorld()->LineTraceSingleByObjectType(HitResult, StartLoc, EndLoc, ObjectParams, FCollisionQueryParams())) {// �ε����� �ݸ��� ä�� �����ʿ�
				// ������ �ε��� ��ġ�� ����
				HitPlace = HitResult.ImpactPoint;

				break;
			}
		}

		if (HitPlace != FVector::ZeroVector) {
			// ����� ��ġ ������ �÷��̾� �̵�
			Player_Archer->SetActorLocation(HitPlace);
		}
		
		Destroy();


		// ����1 - ������ �����ϴ� ��ġ�� GetComponentLocation()�� �Ͽ�����, �̴� ȭ���� �߽����̹Ƿ�, �װ����� ȭ���� ��� �÷��̾ ȭ���� �ε��� ��ġ���� ���� �ڷ� �̵��ϰ� ��. �׷��� ������ ���� ��ġ�� ȭ������ �κ��� �ǵ��� ������ �ʿ䰡 ���� = �ذ�
		
		// ����2 - �÷��̾��� ��ġ �̵��� �ȵ� -> ������ ���̰� �ݸ����� ���� ������ ���������� ���̰� �Ǿ�� ��. �׷��� ������ �ݸ����� �ε����� ��, ������ �ƹ� ���Ϳ��� �ε����� ���ϰ� ��ġ���� �������� ����. ��ġ ���� ������ �÷��̾�� �̵��� ����
			// �Ǵ� ȭ���� ���δ� �ݸ����� ũ�� ��ü�� �ٿ��� ���� ����
			// ���� ������ ���̰� �ʹ� ��� �ʹ� ���� ������ ������, ���̴� �ͺ��� ���� ������ �浹�ؼ� �÷��̾ �ǵ��� �ͺ��� �������� �̵��� �� ����



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
