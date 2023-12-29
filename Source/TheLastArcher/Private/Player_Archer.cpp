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
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>

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


	// Ȱ===========
	BowMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BowMeshComp"));
	BowMeshComp->SetupAttachment(LeftHand);
	BowMeshComp->SetRelativeLocation(FVector(-8.5, 9, -2.5));
	BowMeshComp->SetRelativeRotation(FRotator(13, 90, -90));
	BowMeshComp->SetRelativeScale3D(FVector(1.5, 1.5, 3));

	ConstructorHelpers::FObjectFinder<USkeletalMesh>BowMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/Bow/uploads_files_3856554_bow.uploads_files_3856554_bow'"));

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

	// Ȱ����
	UpBowString = CreateDefaultSubobject<UCableComponent>(TEXT("UpBowString"));
	UpBowString->SetupAttachment(BowMeshComp);
	UpBowString->SetRelativeLocation(FVector(-5, 0, 30));
	UpBowString->NumSegments = 1; // cable�� �ⷷ�̴� ������ ���ֱ�
	UpBowString->CableLength = 10.f; // cable�� ����
	UpBowString->EndLocation = FVector(0); // cable�� end�� ��ġ��

	DownBowString = CreateDefaultSubobject<UCableComponent>(TEXT("DownBowString"));
	DownBowString->SetupAttachment(BowMeshComp);
	DownBowString->SetRelativeLocation(FVector(-4, 0, -30));
	DownBowString->NumSegments = 1; // cable�� �ⷷ�̴� ������ ���ֱ�
	DownBowString->CableLength = 10.f; // cable�� ����
	DownBowString->EndLocation = FVector(0); // cable�� end�� ��ġ��


	// Ȱ===========




	// collision =========================
	// Ȱ ���� collision 
	BowStringCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BowStringComllision"));
	BowStringCollision->SetupAttachment(BowStringPlace);
	BowStringCollision->SetRelativeScale3D(FVector(0.3));

	// ������ ��� collision
	CanShotPlaceCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CanShotPlaceCollision"));
	CanShotPlaceCollision->SetupAttachment(BowStringPlace);
	CanShotPlaceCollision->SetRelativeLocation(FVector(-60, 0, 0));
	
	/*
	// ������ collision
	RightFingerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RightFingerCollision"));
	RightFingerCollision->SetupAttachment(RightHand);
	RightFingerCollision->SetRelativeLocation(FVector(0.6f, 12, -2.5));
	RightFingerCollision->SetRelativeScale3D(FVector(0.2));
	*/


	// collision =========================


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





	// ȭ�� ���� ========================

	// �ʱ�ȭ
	Choose_Normal = true;

	// ȭ�� ������ ��ġ - �ٲ�� ��
	//ArrowSpawnPlace = BowMeshComp->GetBoneTransform(TEXT("bowstring"));
	ArrowSpawnPlace = BowMeshComp->GetRelativeTransform();

	// ȭ�� ���� ========================






	// Ȱ ���� =======================================
	// CableComponent�� ������ �� �ֵ��� �غ��� Mesh�� attach -> BowStringPlace�� ���������ν� Ȱ ������ ������� ��� ���� ����
	UpBowString->SetAttachEndToComponent(BowStringPlace);
	DownBowString->SetAttachEndToComponent(BowStringPlace);



	// Ȱ ���� =======================================



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
		EnhancedInputComponent->BindAction(IA_LeftTrigger, ETriggerEvent::Triggered, this, &APlayer_Archer::LeftTrigger_LoadArrow);


		// �÷��̾� ���� - Ȱ ���� ���, ���� - ������ Ʈ����*
		EnhancedInputComponent->BindAction(IA_RightTrigger, ETriggerEvent::Triggered, this, &APlayer_Archer::RightTrigger_Attack_Ready);
		EnhancedInputComponent->BindAction(IA_RightTrigger, ETriggerEvent::Completed, this, &APlayer_Archer::RightTrigger_Attack_Shot);


		// �÷��̾� ȭ�� ���� ��ȯ - �޼� �׸�*
		EnhancedInputComponent->BindAction(IA_LeftGrip, ETriggerEvent::Triggered, this, &APlayer_Archer::LeftGrip_ChangeArrowType);
		EnhancedInputComponent->BindAction(IA_LeftGrip, ETriggerEvent::Completed, this, &APlayer_Archer::LeftGrip_ChangeArrow_Bool);


		// �÷��̾� Ȱ �κ��丮 ����/�ݱ�

		// �÷��̾� ������ ��� - ������ �׸�*




		// �Ͻ�����
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


	/*
	//BowStringPlace->SetRelativeLocation(RightHand->GetRelativeLocation());

	//BowStringPlace->AttachToComponent(RightHand);

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	BowStringPlace->AttachToComponent(RightHand, AttachmentRules, NAME_None); // ���� �̸� ��� NAME_None ���
	*/


	/*
	// Ȱ���� collision�� RightMesh�� overlap���� ��� - if��
	if (BowStringCollision->IsOverlappingComponent(RightHand) == true) {
		
		UE_LOG(LogTemp, Warning, TEXT("Success overlap"));


		// Ȱ ������ ��ġ�� �������� ���ϰ� ���� ����
		BowStringPlace->SetWorldLocation(RightController->GetSocketLocation(FName("IndexFinger")));

		CatchString_ReadyAttack = true;
	}
	*/

	// Ȱ ������ ��ġ�� �������� ���ϰ� ���� ����
	BowStringPlace->SetWorldLocation(RightController->GetSocketLocation(FName("IndexFinger")));

	float speed = 3000.f;

	if (LoadArrow) {
		
		FVector EndLocation = LoadArrow->GetActorLocation() + ((BowMeshComp->GetComponentLocation() - BowStringPlace->GetComponentLocation())* speed).GetSafeNormal() * 1000.0f;

		//DrawDebugLine( GetWorld(), BowMeshComp->GetComponentLocation(), EndLocation, FColor::Green, false, -1, 0, 2.0f  );
	}


	// ���� �غ� ���·� bool���� true�� ��ȯ

}

void APlayer_Archer::RightTrigger_Attack_Shot(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Right Trigger_Shot"));
	/*
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	BowStringPlace->AttachToComponent(BowMeshComp, AttachmentRules, NAME_None); // ���� �̸� ��� NAME_None ���
	*/

	BowStringPlace->SetRelativeLocation(FVector(-5, 0, 0));




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
		// ȭ���� ���ư��� ����
		GoArrow->ArrowGoingDirection = (BowMeshLocation - BowStringPlaceLocation).GetSafeNormal();

		// AArrow_BaseŬ�������� tick���� ȭ���� ��������, AArrow_Base�� bool������ true�� ��
		GoArrow->bIsShotArrow = true;

		// ȭ�� ������ �����ϵ���
		bIsLoadArrow = false;

	}


}


void APlayer_Archer::LeftThumbStick_Move(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Success Left Stick"));

	FVector2D InputDirection = value.Get<FVector2D>();

	PlayerDirection.X = InputDirection.Y * 0.5f;
	PlayerDirection.Y = InputDirection.X * 0.5f;

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

	// ������ ȭ���� Ȱ ���� ���� ����ġ - Ȱ ���� �����ӿ� ���� ���� ������
	// �����Ǵ� ȭ���� ������ ���� ���õǾ� �ִ� ȭ���� ������ ���� ���õ�
	// -> �����Ǵ� ȭ���� �������� �Լ��� �����, CurrentArrowType�� ���� �Լ��� ���� ����ǵ��� �ؾ� ��

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


	bIsChangeArrow  = false;

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

	LoadArrow = GetWorld()->SpawnActor<AArrow_Base>(Factory_NomalArrow, ArrowSpawnPlace);

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

		LoadArrow->SetActorRelativeLocation(FVector(65, 0.5f, 0));
		LoadArrow->SetActorRelativeRotation(FRotator(67, 137, 146));
		LoadArrow->SetActorRelativeScale3D(FVector(1));




	}
}

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


