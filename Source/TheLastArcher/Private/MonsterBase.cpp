// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"


#include "AI/MonsterAnim.h"
#include "AI/MonsterFSM.h"
#include "StatesComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"



AMonsterBase::AMonsterBase()
{

	PrimaryActorTick.bCanEverTick = true;

	MonsterFsm = CreateDefaultSubobject<UMonsterFSM>(TEXT("MonsterFSM"));
//=======================================================================================================================================

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon -> SetupAttachment(GetMesh(),("WeaponSocket"));
	Weapon -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempWeapon(TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/Sword/Viking_Sword.Viking_Sword'"));
	if(TempWeapon.Succeeded())
	{
		Weapon->SetSkeletalMesh(TempWeapon.Object);
		//(X=-21.432639,Y=9.751223,Z=10.327291)
		//(Pitch=9.846551,Yaw=-100.151081,Roll=178.246217)
		//(X=1.000000,Y=1.000000,Z=1.500000)
		Weapon->SetRelativeLocationAndRotation(FVector(-21.0f,9.75,10.3f),FRotator(9.8f,-100.0f,180.0f));
		Weapon->SetRelativeScale3D(FVector(1.0,1.0,1.5f));
		
	}
	//(X=-1.062823,Y=0.431487,Z=-39.974626)
	//(Pitch=0.000000,Yaw=1.000000,Roll=1.000000)
	WeaponCapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("WeaponCapsuleComp");
	WeaponCapsuleComp -> SetupAttachment(Weapon);
	WeaponCapsuleComp -> SetRelativeLocationAndRotation(FVector(-1.0f,0.431487f,-40.f),FRotator(0.0f,1.0f,1.0f));
	

//=======================================================================================================================================
	HP = CreateDefaultSubobject<UStatesComponent>("HP");
//=======================================================================================================================================

	ArrowComp = CreateDefaultSubobject<UArrowComponent>("ArrowComp");
	ArrowComp -> SetupAttachment(RootComponent);
	ArrowComp -> SetRelativeLocation(FVector(70.0f,0,3.0f));

//=======================================================================================================================================

	ConstructorHelpers::FClassFinder<UMonsterAnim> TempAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/TheLastArchers/KSE/Animations/ABP_NormalMonster.ABP_NormalMonster_C'"));
	if(TempAnim.Succeeded())
	{
		GetMesh()->SetAnimClass(TempAnim.Class);
	}
	// 플레이어를 쳐다보도록한다.
	GetCharacterMovement()->bOrientRotationToMovement = true;
//=======================================================================================================================================

	HPComp = CreateDefaultSubobject<UWidgetComponent>("HPComp");
	HPComp -> SetupAttachment(RootComponent);
	ConstructorHelpers::FClassFinder<UUserWidget>WidgetTemp(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/TheLastArchers/KSE/Blueprints/UI/WBP_HPBar.WBP_HPBar_C'"));
	if(WidgetTemp.Succeeded())
	{
		HPComp->SetWidgetClass(WidgetTemp.Class);
		HPComp->SetDrawSize(FVector2D(150,20));
		HPComp->SetRelativeLocation(FVector(0,0,120));
		HPComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
//=======================================================================================================================================

	UCapsuleComponent* Cap = GetCapsuleComponent();
	auto Meshc = GetMesh();
	Cap->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	Cap->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);

	Meshc->SetCollisionResponseToChannel(ECC_Visibility,ECR_Ignore);
	Meshc->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	
//=======================================================================================================================================

}




void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	// HPComp->GetWidget()->AddToViewport();
	
}


void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// HPUI 빌보드 처리
	FVector Start = HPComp->GetComponentLocation();
	FVector Target = UGameplayStatics::GetPlayerCameraManager(GetWorld(),0)->GetCameraLocation();
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(Start,Target);
	HPComp->SetWorldRotation(NewRotation);

}



