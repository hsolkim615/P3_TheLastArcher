// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Archer.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include <../../../../../../../Plugins/Runtime/XRBase/Source/XRBase/Public/HeadMountedDisplayFunctionLibrary.h>
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>

// Sets default values
APlayer_Archer::APlayer_Archer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ī�޶�
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);

	// Hmd 
	HmdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hmd Mesh"));
	HmdMesh->SetupAttachment(CameraComp);


	// ������
	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	RightController->SetupAttachment(RootComponent);
	RightController->SetRelativeLocation(FVector(30, 40, 0));
	RightController->SetTrackingMotionSource(FName("Right")); // Ʈ��ŷ�� �ʿ�

	RightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(RightController);
	RightHand->SetRelativeRotation(FRotator(45, 0, 90));

	ConstructorHelpers::FObjectFinder<USkeletalMesh>RightHandMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));

	if (RightHandMesh.Succeeded()) {
		RightHand->SetSkeletalMesh(RightHandMesh.Object);
	}


	// �޼�
	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	LeftController->SetupAttachment(RootComponent);
	LeftController->SetRelativeLocation(FVector(30, -40, 0));
	LeftController->SetTrackingMotionSource(FName("Left"));// Ʈ��ŷ�� �ʿ�

	LeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(LeftController);
	LeftHand->SetRelativeRotation(FRotator(-45, -180, 90));

	ConstructorHelpers::FObjectFinder<USkeletalMesh>LeftHandMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'"));

	if (LeftHandMesh.Succeeded()) {
		LeftHand->SetSkeletalMesh(LeftHandMesh.Object);
	}

}

// Called when the game starts or when spawned
void APlayer_Archer::BeginPlay()
{
	Super::BeginPlay();

	// Ʈ��ŷ
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (subsys != nullptr && imc != nullptr) {
			subsys->AddMappingContext(imc, 0);

		}
	}

}

// Called every frame
void APlayer_Archer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// �÷��̾� ���� Ű ���ε�
void APlayer_Archer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

