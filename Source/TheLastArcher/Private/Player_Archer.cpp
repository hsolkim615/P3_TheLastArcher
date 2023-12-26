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

	// ī�޶�
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);

	// Hmd - ��� ��� 
	HmdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hmd Mesh"));
	HmdMesh->SetupAttachment(CameraComp);


	// ������================
	// ������ ��Ʈ�ѷ�
	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	RightController->SetupAttachment(RootComponent);
	RightController->SetRelativeLocation(FVector(30, 40, 0));
	RightController->SetTrackingMotionSource(FName("Right")); // Ʈ��ŷ�� �ʿ�

	// ������ ����
	RightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(RightController);
	RightHand->SetRelativeRotation(FRotator(0, 0, 90));

	ConstructorHelpers::FObjectFinder<USkeletalMesh>RightHandMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));

	if (RightHandMesh.Succeeded()) {
		RightHand->SetSkeletalMesh(RightHandMesh.Object);
	}
	// ������================


	// �޼�==============
	// �޼� ��Ʈ�ѷ�
	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	LeftController->SetupAttachment(RootComponent);
	LeftController->SetRelativeLocation(FVector(30, -40, 0));
	LeftController->SetTrackingMotionSource(FName("Left"));// Ʈ��ŷ�� �ʿ�

	// �޼� ����
	LeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(LeftController);
	LeftHand->SetRelativeRotation(FRotator(0, -180, 90));

	ConstructorHelpers::FObjectFinder<USkeletalMesh>LeftHandMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'"));

	if (LeftHandMesh.Succeeded()) {
		LeftHand->SetSkeletalMesh(LeftHandMesh.Object);
	}
	// �޼�==============



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
	
	// Ʈ��ŷ ����===============
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (subsys != nullptr && InputMappingContext != nullptr) {
			subsys->AddMappingContext(InputMappingContext, 0);
			UE_LOG(LogTemp, Warning, TEXT("Traking Success"));

		}
	}
	// Ʈ��ŷ ����===============





}

// Called every frame
void APlayer_Archer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	// Player �̵�================================
	PlayerDirection.Normalize();

	FTransform ControllerTransform = FTransform(this->GetControlRotation());

	FVector dir = ControllerTransform.TransformVector(PlayerDirection);

	this->AddMovementInput(dir);

	PlayerDirection = FVector::ZeroVector;
	// Player �̵�================================

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



		// �÷��̾� �̵� - �޼� ��ƽ*
		EnhancedInputComponent->BindAction(IA_LeftThumbStick, ETriggerEvent::Triggered, this, &APlayer_Archer::LeftThumbStick_Move);

		// �÷��̾� �þ� �¿� �̵� - ������ ��ƽ* 
		EnhancedInputComponent->BindAction(IA_RightThumbStick, ETriggerEvent::Triggered, this, &APlayer_Archer::RightThumbStick_Turn);

		// �÷��̾� �������� ���� �̵�

		// �÷��̾� ȭ�� ���� - �޼� Ʈ����*

		// �÷��̾� ���� - Ȱ ���� ���, ���� - ������ Ʈ����*
		EnhancedInputComponent->BindAction(IA_RightTrigger, ETriggerEvent::Triggered, this, &APlayer_Archer::RightThumbStick_Attack_Ready);
		EnhancedInputComponent->BindAction(IA_RightTrigger, ETriggerEvent::Completed, this, &APlayer_Archer::RightThumbStick_Attack_Shot);


		// �÷��̾� ȭ�� ���� ��ȯ - �޼� �׸�*
		EnhancedInputComponent->BindAction(IA_LeftTrigger, ETriggerEvent::Triggered, this, &APlayer_Archer::LeftTrigger_ReadyArrow);

		// �÷��̾� Ȱ �κ��丮 ����/�ݱ�

		// �÷��̾� ������ ��� - ������ �׸�*




		// �Ͻ�����
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

	// ���� Ȱ ������ ȭ���� ���ٸ�, ȭ���� ���� / ������ �ƹ��ϵ� ����
	// ������ ȭ���� Ȱ ���� ���� ����ġ - Ȱ ���� �����ӿ� ���� ���� ������
	// �����Ǵ� ȭ���� ������ ���� ���õǾ� �ִ� ȭ���� ������ ���� ���õ�
}


