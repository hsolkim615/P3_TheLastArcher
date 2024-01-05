// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow_Base.h"
#include "Components/CapsuleComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Player_Archer.h"

// Sets default values
AArrow_Base::AArrow_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Arrow의 collision 생성
	ArrowCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ArrowCollisionComp"));
	SetRootComponent(ArrowCollisionComp);
	ArrowCollisionComp->SetRelativeScale3D(FVector(1, 0.4, 1));

	// Arrow의 외형
	ArrowMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMeshComp"));
	ArrowMeshComp->SetupAttachment(ArrowCollisionComp);
	ArrowMeshComp->SetRelativeLocation(FVector(0.4, 0, -0.4));
	ArrowMeshComp->SetWorldRotation(FRotator(-44, -25, 18));
	ArrowMeshComp->SetRelativeScale3D(FVector(3));
	//ArrowMeshComp->SetRelativeScale3D(FVector(2));S

	ConstructorHelpers::FObjectFinder<UStaticMesh>ArrowMesh(TEXT("/Script/Engine.StaticMesh'/Game/Resource/Arrow/WoodenArrow.WoodenArrow'"));

	if (ArrowMesh.Succeeded()) {
		ArrowMeshComp->SetStaticMesh(ArrowMesh.Object);

	}

	// 플레이어 저장
	Player_Archer = Cast<APlayer_Archer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//Player_Archer = GetOwner<APlayer_Archer>();
}

// Called when the game starts or when spawned
void AArrow_Base::BeginPlay()
{
	Super::BeginPlay();

	ArrowCollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);


}

// Called every frame
void AArrow_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	if (bIsShotArrow == true) {

		// ArrowGoingDirection의 방향으로 화살이 날아가도록 함
		this->SetActorLocation(GetActorLocation() + ArrowGoingDirection * ArrowSpeed * DeltaTime);

	}
	*/

	if (bIsShotArrow == true) {
		FVector StartLocation = GetActorLocation();  // 시작 위치
		FVector EndLocation = StartLocation + ArrowGoingDirection * ArrowSpeed * DeltaTime;  // 목표 위치
		FVector MiddleLocation = (StartLocation + EndLocation) / 2.0f;  // 중간 위치

		// 화살이 곡선으로 이동하도록 중간 지점을 향해 설정
		FVector NewDirection = (MiddleLocation - GetActorLocation()).GetSafeNormal();

		this->SetActorLocation(GetActorLocation() + NewDirection * ArrowSpeed * DeltaTime);
	}





}

void AArrow_Base::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);


}

