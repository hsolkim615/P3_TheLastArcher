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
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "StatesComponent.h"
#include "Components/CapsuleComponent.h"
#include "Item_Base.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Blueprint/UserWidget.h>


// Sets default values
APlayer_Archer::APlayer_Archer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스텟 컴퍼넌트 부착
	StatesComp = CreateDefaultSubobject<UStatesComponent>("StatesComp");

	// 카메라
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);

	// Hmd - 머리
	HmdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hmd Mesh"));
	HmdMesh->SetupAttachment(CameraComp);


	// 오른손================
	// 오른손 컨트롤러
	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	RightController->SetupAttachment(RootComponent);
	//RightController->SetRelativeLocation(FVector(30, 40, 0));
	RightController->SetTrackingMotionSource(FName("Right")); // 오른손에 매치

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
	//LeftController->SetRelativeLocation(FVector(30, -40, 0));
	LeftController->SetTrackingMotionSource(FName("Left"));// 왼손에 매치

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
	// 활 본체
	BowMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BowMeshComp"));
	BowMeshComp->SetupAttachment(LeftHand);
	BowMeshComp->SetRelativeLocation(FVector(-8.5, 9, -2.5));
	BowMeshComp->SetRelativeRotation(FRotator(13, 90, 90));
	BowMeshComp->SetRelativeScale3D(FVector(1.5, 1.5, 3));

	ConstructorHelpers::FObjectFinder<USkeletalMesh>BowMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/Bow/Bow.Bow'"));

	if (BowMesh.Succeeded()) {
		BowMeshComp->SetSkeletalMesh(BowMesh.Object);
	}

	BowStringPlace = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BowStringPlace"));
	BowStringPlace->SetupAttachment(BowMeshComp);
	BowStringPlace->SetRelativeLocation(FVector(-5, 0, 0));

	/*
	BowStringPlace->SetRelativeScale3D(FVector(0.005));

	ConstructorHelpers::FObjectFinder<UStaticMesh>BSPMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));

	if (BSPMesh.Succeeded()) {
		BowStringPlace->SetStaticMesh(BSPMesh.Object);

	}
	*/

	// 활 시위
	UpBowString = CreateDefaultSubobject<UCableComponent>(TEXT("UpBowString"));
	UpBowString->SetupAttachment(BowMeshComp);
	UpBowString->SetRelativeLocation(FVector(-5, 0, 30));
	UpBowString->NumSegments = 1; // cable의 장력 - 작을 수록 탄탄해짐
	UpBowString->CableLength = 10.f; // cable의 길이
	UpBowString->EndLocation = FVector(0); // cable의 end 위치 값

	DownBowString = CreateDefaultSubobject<UCableComponent>(TEXT("DownBowString"));
	DownBowString->SetupAttachment(BowMeshComp);
	DownBowString->SetRelativeLocation(FVector(-4, 0, -30));
	DownBowString->NumSegments = 1; // cable의 장력 - 작을 수록 탄탄해짐
	DownBowString->CableLength = 10.f; // cable의 길이
	DownBowString->EndLocation = FVector(0); // cable의 end 위치 값


	// 활===========




	// collision =========================
	// 활 시위 collision 
	BowStringCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BowStringComllision"));
	BowStringCollision->SetupAttachment(BowStringPlace);
	BowStringCollision->SetRelativeScale3D(FVector(0.15f));


	// 화살을 쏠 수 있는 구역 collision
	CanShotPlaceCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CanShotPlaceCollision"));
	CanShotPlaceCollision->SetupAttachment(BowMeshComp);
	CanShotPlaceCollision->SetRelativeLocation(FVector(-45, 0, 0));
	CanShotPlaceCollision->SetRelativeScale3D(FVector(0.5f));



	// 오른손 컨트롤러 collision
	RightFingerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RightFingerCollision"));
	RightFingerCollision->SetupAttachment(RightHand);
	RightFingerCollision->SetRelativeLocation(FVector(0.6f, 12, -2.5));
	RightFingerCollision->SetRelativeScale3D(FVector(0.2));
	// collision =========================


	// UI ===================================
	UI_PlayerHP = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI_PlayerHP"));
	UI_PlayerHP->SetupAttachment(BowMeshComp);
	UI_PlayerHP->SetRelativeScale3D(FVector(0.01));
	UI_PlayerHP->SetRelativeLocation(FVector(0, 0, 10));
	UI_PlayerHP->SetRelativeRotation(FRotator(0, 180, 90));
	UI_PlayerHP->SetVisibility(true);

	ConstructorHelpers::FClassFinder<UUserWidget>W_UI_PlayerHP(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/TheLastArchers/KHS/UI/WBP_PlayerHP_UI.WBP_PlayerHP_UI'"));

	if (W_UI_PlayerHP.Succeeded()) {
		UI_PlayerHP->SetWidgetClass(W_UI_PlayerHP.Class);
	}

	/* *********************
	// ������ ȭ���� ���� �ʱ�ȭ - Normal
	CurrentArrowType = EArrowType::NormalArrow;
	*/







}

// Called when the game starts or when spawned
void APlayer_Archer::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Start Log ======================================================"));

	// 트레킹 설정===============
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (subsys != nullptr && InputMappingContext != nullptr) {
			subsys->AddMappingContext(InputMappingContext, 0);
			UE_LOG(LogTemp, Warning, TEXT("Traking Success"));

		}
	}
	// 트레킹 설정===============



	// 화살 설정 ========================

	// 장전 가능한 화살 Normal로 초기화
	Choose_Normal = true;

	// 화살을 시폰할 위치 값 초기화
	//ArrowSpawnPlace = BowMeshComp->GetBoneTransform(TEXT("bowstring"));
	ArrowSpawnPlace = BowMeshComp->GetRelativeTransform();

	// 화살 설정 ========================



	// 활 시위 =======================================
	// CableComponent를 활 시위 중심Mesh에 attach -> BowStringPlace의 위치 값의 변화를 CableCompoenet들이 따라 다녀, 활 시위를 당기는 모습을 연출할 수 있음
	UpBowString->SetAttachEndToComponent(BowStringPlace);
	DownBowString->SetAttachEndToComponent(BowStringPlace);

	// 활 시위 =======================================



}

// Called every frame
void APlayer_Archer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Player 이동================================
	PlayerDirection.Normalize();

	FTransform ControllerTransform = FTransform(this->GetControlRotation());

	FVector dir = ControllerTransform.TransformVector(PlayerDirection);

	this->AddMovementInput(dir * 0.5f);

	PlayerDirection = FVector::ZeroVector;
	// Player 이동================================



	// UI===========================================
	//SetCurrentPlayerHP(StatesComp->MaxHealth, StatesComp->CurrentHealth);

	/*
	FVector ForwardVector = CameraComp->GetForwardVector();
	FRotator LookAtRotation = FRotationMatrix::MakeFromX(ForwardVector).Rotator();

	// �÷��̾��� yaw�� ���� ���� �þ� ������ ������Ʈ�մϴ�.
	SetActorRotation(FRotator(0, LookAtRotation.Yaw, 0));
	*/


	/*
	//
	if (CameraComp->GetRelativeRotation().Yaw != 0.f) {

		//this->SetActorRotation(FRotator(this->GetActorRotation().Pitch, (this->GetActorRotation().Yaw + CameraComp->GetRelativeRotation().Yaw), this->GetActorRotation().Roll));

		//AddControllerYawInput(this->GetActorRotation().Yaw + CameraComp->GetRelativeRotation().Yaw);


		CameraComp->SetRelativeRotation(FRotator(0));
	}
	*/
}

// �÷��̾� ���� Ű ���ε�
void APlayer_Archer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// PlayerInputComponent ����ȯ
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);


	if (EnhancedInputComponent) {
		// *****�÷��̾� ���� Ű ���ε� ����
		// ������ - ��ƽ* / �׸�* / Ʈ����* / A / B
		// �޼� - ��ƽ* / �׸�* / Ʈ����* / X / Y



		// 플레이어 이동 - 왼손 스틱
		EnhancedInputComponent->BindAction(IA_LeftThumbStick, ETriggerEvent::Triggered, this, &APlayer_Archer::LeftThumbStick_Move);

		// 플레이어 시야 움직임 - 오른손 스틱
		EnhancedInputComponent->BindAction(IA_RightThumbStick, ETriggerEvent::Triggered, this, &APlayer_Archer::RightThumbStick_Turn);

		// �÷��̾� �������� ���� �̵�

		// �÷��̾� ȭ�� ���� - �޼� Ʈ����*
		EnhancedInputComponent->BindAction(IA_LeftTrigger, ETriggerEvent::Triggered, this, &APlayer_Archer::LeftTrigger_LoadArrow);


		// �÷��̾� ���� - Ȱ ���� ���, ���� - ������ Ʈ����*
		EnhancedInputComponent->BindAction(IA_RightTrigger, ETriggerEvent::Triggered, this, &APlayer_Archer::RightTrigger_Attack_Ready);
		EnhancedInputComponent->BindAction(IA_RightTrigger, ETriggerEvent::Completed, this, &APlayer_Archer::RightTrigger_Attack_Shot);


		// �÷��̾� ȭ�� ���� ��ȯ - �޼� �׸�*
		EnhancedInputComponent->BindAction(IA_LeftGrip, ETriggerEvent::Triggered, this, &APlayer_Archer::LeftGrip_ChangeArrowType);
		EnhancedInputComponent->BindAction(IA_LeftGrip, ETriggerEvent::Completed, this, &APlayer_Archer::LeftGrip_ChangeArrow_Bool);


		// �÷��̾� Ȱ �κ��丮 ����/�ݱ�
		EnhancedInputComponent->BindAction(IA_RightGrip, ETriggerEvent::Triggered, this, &APlayer_Archer::RightGrip_TakeItem);

		// �÷��̾� ������ ��� - ������ �׸�*




		// �Ͻ�����
	}
}

void APlayer_Archer::RightThumbStick_Turn(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Right Stick"));

	// �÷��̾��� �þ߰����� �� ������ �����ؾ� ��
	// �켱���� 1�� ���̽�ƽ, �켱���� 2�� ī�޶��� Rotation ������


	float PlayerRotation = 0.3f * value.Get<float>();
	AddControllerYawInput(PlayerRotation);



}

void APlayer_Archer::RightTrigger_Attack_Ready(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Right Trigger_Ready"));



	if (BowStringCollision->IsOverlappingComponent(RightFingerCollision) == true) {
		// Ȱ ������ ��ġ�� �������� ���ϰ� ���� ���� - LoadArrow�� Ȱ ������ �پ� �����Ƿ�, ����
		// x�� ��ġ ���� �ʿ�
		BowStringPlace->SetRelativeLocation(FVector(RightController->GetRelativeLocation().X - 30.f, BowStringPlace->GetRelativeLocation().Y, BowStringPlace->GetRelativeLocation().Z));


		// ȭ�� ���ư��� ���̵� ����
		if (LoadArrow) {
			// ������ + ���� + ������ ����
			FVector EndLocation = LoadArrow->GetActorLocation() + ((BowMeshComp->GetComponentLocation() - BowStringPlace->GetComponentLocation())).GetSafeNormal() * 2000.0f;

			// ����ȣ�� ���
			DrawDebugLine(GetWorld(), BowStringPlace->GetComponentLocation(), EndLocation, FColor::Green, false, -1, 0, 2.0f);
		}


	}



}

void APlayer_Archer::RightTrigger_Attack_Shot(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Right Trigger_Shot"));



	if (BowStringCollision->IsOverlappingComponent(CanShotPlaceCollision) == true) {



		// ������ collision�� shot collision�� overlap ���� ��� - if��

		if (LoadArrow) {

			GoArrow = LoadArrow;
			LoadArrow->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			LoadArrow = nullptr;

		}

		// ===============
		FVector BowMeshLocation = BowMeshComp->GetComponentLocation(); // Ȱ�� ��ġ
		FVector BowStringPlaceLocation = BowStringPlace->GetComponentLocation(); // Ȱ ������ ��ġ

		if (GoArrow) {

			GoArrow->ArrowCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

			// 화살 날아가는 방향 설정
			GoArrow->ArrowGoingDirection = (BowMeshLocation - BowStringPlaceLocation).GetSafeNormal();

			// AArrow_Base의 tick에서 화살이 날아가는 위치를 갱신하므로, AArrow_Base의 bool변수를 true로 해준다. 
			GoArrow->bIsShotArrow = true;

			// 화살은 발사되고 10초 뒤에 사라진다. 
			GoArrow->SetLifeSpan(10.f);

			// 화살이 장전되도록 한다. 
			if (bIsLoadArrow == true) {
				bIsLoadArrow = false;
			}

		}

	}

	// 활 시위를 원래 위치로 설정
	BowStringPlace->SetRelativeLocation(FVector(-5, 0, 0));

}

void APlayer_Archer::RightGrip_TakeItem(const FInputActionValue& value)
{
	// 




	class AItem_Base* HitItem;

	// 충돌한 컴포넌트를 저장할 배열
	TArray<UPrimitiveComponent*> OverlappingComponents;
	// 충도돌한 컴포넌트 배열에 저장
	GetOverlappingComponents(OverlappingComponents);
	// 라인 트레이스 시작점  
	FVector StartLoc = RightController->GetComponentLocation();
	// 라인 트레이스 시작점  
	FVector EndLoc = StartLoc + FVector(100, 0, 0);
	// 시작점에서 도착점으로 라인이 나가는 동안, 부딪힌 액터가 있을 것

	FCollisionObjectQueryParams ObjectParams;
	// Item콜리전 채널만 감지하도록 함
	ObjectParams.AddObjectTypesToQuery(ECC_GameTraceChannel10);

	// 라인 트레이스를 실행하고, Item Collision인지 감지하고, 만약 Item이라면 플레이어의 손으로 끌어당김
	// OverlappingComponents의 크기만큼 반복 - 아마 1일 것
	for (UPrimitiveComponent* Component : OverlappingComponents) {
		// 부딪힌 결과 값
		FHitResult HitResult;
		// 라인이 부딪힌 경우
		if (GetWorld()->LineTraceSingleByObjectType(HitResult, StartLoc, EndLoc, ObjectParams, FCollisionQueryParams())) {
			// 라인이 부딪힌 위치를 저장

			HitItem = Cast<AItem_Base>(HitResult.GetActor());

			break;
		}
	}
	/*
	if (HitItem) {
		// 저장된 위치 값으로 플레이어 이동
		HitItem->SetActorLocation(RightController->GetComponentLocation());
	}
	*/
}


void APlayer_Archer::LeftThumbStick_Move(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Left Stick"));

	FVector2D InputDirection = value.Get<FVector2D>();

	PlayerDirection.X = InputDirection.Y;
	PlayerDirection.Y = InputDirection.X;

}

void APlayer_Archer::LeftTrigger_LoadArrow(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Left Trigger"));

	// ���� Ȱ ������ ȭ���� ���ٸ�, ȭ���� ���� / ������ �ƹ��ϵ� ����

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

}

void APlayer_Archer::LeftGrip_ChangeArrowType(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Left Grip_Pressed"));

	// �Լ� �ݺ� �ȵǵ��� bool�� �߰� �ʿ� 


	/* ****************************
	int32 NextTypeValue = static_cast<int32>(CurrentArrowType) + 1;

	if (NextTypeValue >= static_cast<int32>(EArrowType::ReturnFNormal))
	{
		// Enum�� ������ ������ ũ�ų� ������ �ٽ� NormalArrow�� ��ȯ
		CurrentArrowType = EArrowType::NormalArrow;
	}
	else
	{
		// ���� Enum �� ��ȯ
		CurrentArrowType = static_cast<EArrowType>(NextTypeValue);
	}
	*/

	if (bIsChangeArrow == true) {

		if (Choose_Normal == true) {

			Choose_Normal = false;

			Choose_Teleport = true;

		}
		else if (Choose_Teleport == true) {

			Choose_Teleport = false;

			Choose_Normal = true;


			/*
			if (GetItemFire == true) {

				Choose_Fire = true;
			}
			else if (GetItemFire == false) {

				Choose_Normal = true;

			}
			*/
		}
		/*
		else if (Choose_Fire == true) {

			Choose_Fire = false;

			Choose_Normal = true;
		}
		*/
	}


	bIsChangeArrow = false;

}

void APlayer_Archer::LeftGrip_ChangeArrow_Bool(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Left Grip_Released"));

	bIsChangeArrow = true;
}


// ������ ȭ�� ���� �Լ�
void APlayer_Archer::Spawn_NormalArrowFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("Success Normal"));

	// ȭ�� ����
	LoadArrow = GetWorld()->SpawnActor<AArrow_Base>(Factory_NomalArrow, ArrowSpawnPlace);

	// ȭ�� ��ġ ����
	SetLoadArrow_Load();
}

void APlayer_Archer::Spawn_TeleportArrowFunc()
{

	LoadArrow = GetWorld()->SpawnActor<AArrow_Base>(Factory_TeleportArrow, ArrowSpawnPlace);

	SetLoadArrow_Load();

}

void APlayer_Archer::Spawn_FireArrowFunc()
{

	LoadArrow = GetWorld()->SpawnActor<AArrow_Base>(Factory_FireArrow, ArrowSpawnPlace);

	SetLoadArrow_Load();

}

void APlayer_Archer::SetLoadArrow_Load()
{
	// ������ ȭ�� ����
	if (LoadArrow) {
		LoadArrow->AttachToComponent(BowStringPlace, FAttachmentTransformRules::KeepRelativeTransform);
		//LoadArrow->SetActorTransform(BowMeshComp->GetBoneTransform(TEXT("bowstring")));

		LoadArrow->SetActorRelativeLocation(FVector(65, 0.2f, 0));
		LoadArrow->SetActorRelativeRotation(FRotator(68, 135, 144.5f));
		LoadArrow->SetActorRelativeScale3D(FVector(1));



	}
}

// �� �Լ� �ʿ� ����
void APlayer_Archer::SetLoadArrow_Ready()
{

	if (LoadArrow) {
		//LoadArrow->AttachToComponent(BowStringPlace, FAttachmentTransformRules::KeepRelativeTransform);
		//LoadArrow->SetActorTransform(BowMeshComp->GetBoneTransform(TEXT("bowstring")));

		/*
		LoadArrow->SetActorRelativeLocation(FVector(30, -1, 0));
		LoadArrow->SetActorRelativeRotation(FRotator(-46, -67, 59));
		LoadArrow->SetActorScale3D(FVector(2));
		*/

		LoadArrow->SetActorRelativeLocation(FVector(0));
		LoadArrow->SetActorRelativeRotation(FRotator(0));
		LoadArrow->SetActorScale3D(FVector(3));



	}
}

