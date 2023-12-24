// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Archer.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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



	BowMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BowMeshComp"));
	BowMeshComp->SetupAttachment(LeftHand);

	ConstructorHelpers::FObjectFinder<USkeletalMesh>BowMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/Bow/uploads_files_3856554_bow.uploads_files_3856554_bow'"));

	if (BowMesh.Succeeded()) {
		BowMeshComp->SetSkeletalMesh(BowMesh.Object);
	}

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

		// 플레이어 공격 - 활 시위 잡기, 놓기 - 오른손 트리거*
		EnhancedInputComponent->BindAction(IA_RightTrigger, ETriggerEvent::Triggered, this, &APlayer_Archer::RightThumbStick_Attack_Ready);
		EnhancedInputComponent->BindAction(IA_RightTrigger, ETriggerEvent::Completed, this, &APlayer_Archer::RightThumbStick_Attack_Shot);


		// 플레이어 화살 종류 전환 - 왼손 그립*
		EnhancedInputComponent->BindAction(IA_LeftTrigger, ETriggerEvent::Triggered, this, &APlayer_Archer::LeftTrigger_ReadyArrow);

		// 플레이어 활 인벤토리 열기/닫기

		// 플레이어 아이템 잡기 - 오른손 그립*




		// 일시정지
	}
}

void APlayer_Archer::RightThumbStick_Turn(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Right Stick"));

	float PlayerRotation = value.Get<float>();
	AddControllerYawInput(PlayerRotation);

}

void APlayer_Archer::RightThumbStick_Attack_Ready(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Right Trigger_Ready"));









}

void APlayer_Archer::RightThumbStick_Attack_Shot(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Right Trigger_Shot"));

}


void APlayer_Archer::LeftThumbStick_Move(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Left Stick"));

	FVector2D InputDirection = value.Get<FVector2D>();

	PlayerDirection.X = InputDirection.Y;
	PlayerDirection.Y = InputDirection.X;

}

void APlayer_Archer::LeftTrigger_ReadyArrow(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Left Trigger"));

	// 만약 활 시위에 화살이 없다면, 화살을 스폰 / 있으면 아무일도 없음
	// 스폰된 화살은 활 시위 본에 어테치 - 활 시위 움직임에 따라 같이 움직임
	// 스폰되는 화살의 종류는 현재 선택되어 있는 화살의 종류에 따라 선택됨
}


