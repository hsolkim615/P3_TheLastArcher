// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Archer.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Arrow_Base.h"
#include "Arrow_Type/Arrow_Normal.h"
#include "Arrow_Type/Arrow_Teleport.h"
#include "Arrow_Type/Arrow_Fire.h"
#include "CableComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>

// Sets default values
APlayer_Archer::APlayer_Archer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 카메라
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);

	// Hmd - 기기 헤드 
	HmdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hmd Mesh"));
	HmdMesh->SetupAttachment(CameraComp);


	// 오른손================
	// 오른손 컨트롤러
	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	RightController->SetupAttachment(RootComponent);
	RightController->SetRelativeLocation(FVector(30, 40, 0));
	RightController->SetTrackingMotionSource(FName("Right")); // 트래킹에 필요

	// 오른손 외형
	RightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(RightController);
	RightHand->SetRelativeRotation(FRotator(0, 0, 90));

	ConstructorHelpers::FObjectFinder<USkeletalMesh>RightHandMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));

	if (RightHandMesh.Succeeded()) {
		RightHand->SetSkeletalMesh(RightHandMesh.Object);
	}
	// 오른손================


	// 왼손==============
	// 왼손 컨트롤러
	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	LeftController->SetupAttachment(RootComponent);
	LeftController->SetRelativeLocation(FVector(30, -40, 0));
	LeftController->SetTrackingMotionSource(FName("Left"));// 트래킹에 필요

	// 왼손 외형
	LeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(LeftController);
	LeftHand->SetRelativeRotation(FRotator(0, -180, 90));

	ConstructorHelpers::FObjectFinder<USkeletalMesh>LeftHandMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'"));

	if (LeftHandMesh.Succeeded()) {
		LeftHand->SetSkeletalMesh(LeftHandMesh.Object);
	}
	// 왼손==============


	// 활===========
	BowMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BowMeshComp"));
	BowMeshComp->SetupAttachment(LeftHand);

	ConstructorHelpers::FObjectFinder<USkeletalMesh>BowMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/Bow/uploads_files_3856554_bow.uploads_files_3856554_bow'"));

	if (BowMesh.Succeeded()) {
		BowMeshComp->SetSkeletalMesh(BowMesh.Object);
	}

	BowStringPlace = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BowStringPlace"));
	BowStringPlace->SetupAttachment(BowMeshComp);
	BowStringPlace->SetRelativeLocation(FVector(-5, 0, 0));

	// 활시위
	UpBowString = CreateDefaultSubobject<UCableComponent>(TEXT("UpBowString"));
	UpBowString->SetupAttachment(BowMeshComp);
	UpBowString->SetRelativeLocation(FVector(-5, 0, 30)); 
	UpBowString->NumSegments = 1; // cable의 출렁이는 움직임 없애기
	UpBowString->CableLength = 10.f; // cable의 길이
	UpBowString->EndLocation = FVector(0); // cable의 end의 위치값

	DownBowString = CreateDefaultSubobject<UCableComponent>(TEXT("DownBowString"));
	DownBowString->SetupAttachment(BowMeshComp);
	DownBowString->SetRelativeLocation(FVector(-4,0, -30));
	DownBowString->NumSegments = 1; // cable의 출렁이는 움직임 없애기
	DownBowString->CableLength = 10.f; // cable의 길이
	DownBowString->EndLocation = FVector(0); // cable의 end의 위치값


	// 활===========




	/* *********************
	// 스폰될 화살의 종류 초기화 - Normal
	CurrentArrowType = EArrowType::NormalArrow;
	*/

}

// Called when the game starts or when spawned
void APlayer_Archer::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Start Log ======================================================"));

	// 트래킹 설정===============
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (subsys != nullptr && InputMappingContext != nullptr) {
			subsys->AddMappingContext(InputMappingContext, 0);
			UE_LOG(LogTemp, Warning, TEXT("Traking Success"));

		}
	}
	// 트래킹 설정===============





	// 화살 관련 ========================

	// 초기화
	Choose_Normal = true;

	// 화살 스폰될 위치 - 바꿔야 됨
	ArrowSpawnPlace = BowMeshComp->GetBoneTransform(TEXT("bowstring"));


	// 화살 관련 ========================






	// 활 관련 =======================================
	// CableComponent를 움직일 수 있도록 준비한 Mesh에 attach -> BowStringPlace를 움직임으로써 활 시위가 당겨지는 모습 연출 가능
	UpBowString->SetAttachEndToComponent(BowStringPlace);
	DownBowString->SetAttachEndToComponent(BowStringPlace);



	// 활 관련 =======================================



}

// Called every frame
void APlayer_Archer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	// Player 이동================================
	PlayerDirection.Normalize();

	FTransform ControllerTransform = FTransform(this->GetControlRotation());

	FVector dir = ControllerTransform.TransformVector(PlayerDirection);

	this->AddMovementInput(dir);

	PlayerDirection = FVector::ZeroVector;
	// Player 이동================================






	// 스폰된 화살 설정
	if (LoadArrow) {
		LoadArrow->AttachToComponent(BowMeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		//LoadArrow->SetActorTransform(BowMeshComp->GetBoneTransform(TEXT("bowstring")));

		LoadArrow->SetActorRelativeLocation(FVector(25, 1, 1));
		LoadArrow->SetActorRelativeRotation(FRotator(0, -50, -50));
		LoadArrow->SetActorScale3D(FVector(2));

		/*
		FVector LoadArrowLocation = BowMeshComp->GetBoneTransform(BowMeshComp->GetBoneIndex(TEXT("bowstring"))).GetLocation();
		LoadArrow->SetActorRelativeLocation(LoadArrowLocation);

		*/


	}




	// 화살 발사=====================================================

	if (GoArrow) {

		// 화살 위치 업데이트
		NewArrowPosition = GoArrow->GetActorLocation() + ArrowDirection * ArrowSpeed * GetWorld()->DeltaRealTimeSeconds;

		GoArrow->SetActorLocation(NewArrowPosition);

	}

}

// 플레이어 조작 키 바인딩
void APlayer_Archer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// PlayerInputComponent 형변환
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);


	if (EnhancedInputComponent) {
		// *****플레이어 조작 키 바인딩 구현
		// 오른손 - 스틱* / 그립* / 트리거* / A / B
		// 왼손 - 스틱* / 그립* / 트리거* / X / Y



		// 플레이어 이동 - 왼손 스틱*
		EnhancedInputComponent->BindAction(IA_LeftThumbStick, ETriggerEvent::Triggered, this, &APlayer_Archer::LeftThumbStick_Move);

		// 플레이어 시야 좌우 이동 - 오른손 스틱* 
		EnhancedInputComponent->BindAction(IA_RightThumbStick, ETriggerEvent::Triggered, this, &APlayer_Archer::RightThumbStick_Turn);

		// 플레이어 전방으로 빠른 이동

		// 플레이어 화살 장전 - 왼손 트리거*
		EnhancedInputComponent->BindAction(IA_LeftTrigger, ETriggerEvent::Triggered, this, &APlayer_Archer::LeftTrigger_LoadArrow);


		// 플레이어 공격 - 활 시위 잡기, 놓기 - 오른손 트리거*
		EnhancedInputComponent->BindAction(IA_RightTrigger, ETriggerEvent::Triggered, this, &APlayer_Archer::RightTrigger_Attack_Ready);
		EnhancedInputComponent->BindAction(IA_RightTrigger, ETriggerEvent::Completed, this, &APlayer_Archer::RightTrigger_Attack_Shot);


		// 플레이어 화살 종류 전환 - 왼손 그립*
		EnhancedInputComponent->BindAction(IA_LeftGrip, ETriggerEvent::Triggered, this, &APlayer_Archer::LeftGrip_ChangeArrowType);

		// 플레이어 활 인벤토리 열기/닫기

		// 플레이어 아이템 잡기 - 오른손 그립*




		// 일시정지
	}
}

void APlayer_Archer::RightThumbStick_Turn(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Right Stick"));

	float PlayerRotation = 0.2f * value.Get<float>();
	AddControllerYawInput(PlayerRotation);

}

void APlayer_Archer::RightTrigger_Attack_Ready(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Right Trigger_Ready"));

	// 활 시위를 오른손에 attach 혹은 오른손 검지에 attach

	//BowStringPlace->SetRelativeLocation(RightHand->GetRelativeLocation());

	//BowStringPlace->AttachToComponent(RightHand);


	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	BowStringPlace->AttachToComponent(RightHand, AttachmentRules, NAME_None); // 소켓 이름 대신 NAME_None 사용



	// 공격 준비 상태로 bool변수 true로 전환

}

void APlayer_Archer::RightTrigger_Attack_Shot(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Right Trigger_Shot"));

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	BowStringPlace->AttachToComponent(BowMeshComp, AttachmentRules, NAME_None); // 소켓 이름 대신 NAME_None 사용

	BowStringPlace->SetRelativeLocation(FVector(-5, 0, 0));

	// 화살 발사


	if (LoadArrow) {
		GoArrow = LoadArrow;

		LoadArrow = nullptr;
	}


}


void APlayer_Archer::LeftThumbStick_Move(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Left Stick"));

	FVector2D InputDirection = value.Get<FVector2D>();

	PlayerDirection.X = InputDirection.Y * 0.3f;
	PlayerDirection.Y = InputDirection.X * 0.3f;

}

void APlayer_Archer::LeftTrigger_LoadArrow(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Left Trigger"));

	// 만약 활 시위에 화살이 없다면, 화살을 스폰 / 있으면 아무일도 없음

	if (bIsLoadArrow == false) {

		/* ************
		if (CurrentArrowType == EArrowType::NormalArrow) {

			Spawn_NormalArrowFunc();

		}
		else if (CurrentArrowType == EArrowType::TeleportArrow) {

			Spawn_TeleportArrowFunc();

		}
		else if (CurrentArrowType == EArrowType::FireArrow) {

			Spawn_FireArrowFunc();

		}
		*/

		if (Choose_Normal == true) {

			Spawn_NormalArrowFunc();

		}
		else if (Choose_Teleport == true) {

			Spawn_TeleportArrowFunc();

		}
		else if (Choose_Fire == true) {

			Spawn_FireArrowFunc();

		}

		bIsLoadArrow = true;


	}

	// 스폰된 화살은 활 시위 본에 어테치 - 활 시위 움직임에 따라 같이 움직임
	// 스폰되는 화살의 종류는 현재 선택되어 있는 화살의 종류에 따라 선택됨
	// -> 스폰되는 화살의 종류마다 함수를 만들고, CurrentArrowType에 따라 함수가 각각 실행되도록 해야 함

}

void APlayer_Archer::LeftGrip_ChangeArrowType(const FInputActionValue& value)
{

	// 함수 반복 안되도록 bool값 추가 필요 


	/* ****************************
	int32 NextTypeValue = static_cast<int32>(CurrentArrowType) + 1;

	if (NextTypeValue >= static_cast<int32>(EArrowType::ReturnFNormal))
	{
		// Enum의 마지막 값보다 크거나 같으면 다시 NormalArrow로 순환
		CurrentArrowType = EArrowType::NormalArrow;
	}
	else
	{
		// 다음 Enum 값 반환
		CurrentArrowType = static_cast<EArrowType>(NextTypeValue);
	}
	*/



	if (Choose_Normal == true) {

		Choose_Normal = false;

		Choose_Teleport = true;

	}
	else if (Choose_Teleport == true) {

		Choose_Teleport = false;

		if (GetItemFire == true) {

			Choose_Fire = true;
		}
		else if (GetItemFire == false) {

			Choose_Normal = true;

		}

	}
	else if (Choose_Fire == true) {

		Choose_Fire = false;

		Choose_Normal = true;
	}




}


// 스폰될 화살 종류 함수
void APlayer_Archer::Spawn_NormalArrowFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("Success Normal"));

	LoadArrow = GetWorld()->SpawnActor<AArrow_Base>(Factory_NomalArrow, ArrowSpawnPlace);

}

void APlayer_Archer::Spawn_TeleportArrowFunc()
{

	LoadArrow = GetWorld()->SpawnActor<AArrow_Base>(Factory_TeleportArrow, ArrowSpawnPlace);

}

void APlayer_Archer::Spawn_FireArrowFunc()
{

	LoadArrow = GetWorld()->SpawnActor<AArrow_Base>(Factory_FireArrow, ArrowSpawnPlace);

}


