// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Player_Archer.generated.h"

/* ***************
UENUM(BlueprintType)
enum class EArrowType : uint8 
{
	NormalArrow,
	TeleportArrow,
	FireArrow,
	ReturnFNormal
};
*/

UCLASS()
class THELASTARCHER_API APlayer_Archer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_Archer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	// 생성자 ==============
	// 카메라
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UCameraComponent* CameraComp;

	// Hmd
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UStaticMeshComponent* HmdMesh;

	// 오른손
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UMotionControllerComponent* RightController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class USkeletalMeshComponent* RightHand;

	// 왼손
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UMotionControllerComponent* LeftController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class USkeletalMeshComponent* LeftHand;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UInputMappingContext* InputMappingContext;


	// 활
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class USkeletalMeshComponent* BowMeshComp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components") 
	class UStaticMeshComponent* BowStringPlace;	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components") 
	class UCableComponent* UpBowString;
	//TObjectPtr<class UCableComponent> UPBowString;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UCableComponent* DownBowString;



	// Collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* BowStringCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* CanShotPlaceCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* RightFingerCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsNowOverlaping_RightHand_BowString = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsNowOverlaping_RightHand_ShotPoint = false;


	// 생성자 ==============


public: // BindKey
	// 오른손 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_RightThumbStick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_RightTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_RightGrip;



	// 왼손 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_LeftThumbStick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_LeftTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_LeftGrip;

public:
	// 언리얼에서 스폰할 화살 - 추후 수정 필요 ================
	UPROPERTY(EditAnywhere, Category = Spawn_ArrowType)
	TSubclassOf<class AArrow_Base> Factory_NomalArrow;

	UPROPERTY(EditAnywhere, Category = Spawn_ArrowType)
	TSubclassOf<class AArrow_Base> Factory_TeleportArrow;
	
	UPROPERTY(EditAnywhere, Category = Spawn_ArrowType)
	TSubclassOf<class AArrow_Base> Factory_FireArrow;
	// 언리얼에서 스폰할 화살 - 추후 수정 필요 ================

	// 화살 스폰될 위치 
	FTransform ArrowSpawnPlace;
	



	bool Choose_Normal = false;
	bool Choose_Teleport = false;
	bool Choose_Fire = false;

	bool GetItemFire = false;


	


private: // Bind Function
	// 필요한 변수

	// 플레이어의 이동 방향
	FVector PlayerDirection;

	// 장전된 화살 변수
	bool bIsLoadArrow = false;

	// 장전 중인 Arrow
	class AArrow_Base* LoadArrow;

	// 앞으로 나가는 화살
	class AArrow_Base* GoArrow;

	FVector NewArrowPosition;

	// 공격 준비 상태로 bool변수 false로 전환
	bool CatchString_ReadyAttack = false;


	bool bIsChangeArrow = true;




	// 오른손 입력
	void RightThumbStick_Turn(const FInputActionValue& value); // 플레이어 움직임

	void RightTrigger_Attack_Ready(const FInputActionValue& value); // 플레이어 공격 - 화살 잡기 
	void RightTrigger_Attack_Shot(const FInputActionValue& value); // 플레이어 공격 - 화살 놓기


	// 왼손 입력
	void LeftThumbStick_Move(const FInputActionValue& value); // 플레이어 시야 각도

	void LeftTrigger_LoadArrow(const FInputActionValue& value); // 플레이어 화살 장전

	void LeftGrip_ChangeArrowType(const FInputActionValue& value); // 플레이어 화살 종류 전환
	void LeftGrip_ChangeArrow_Bool(const FInputActionValue& value); // 플레이어 화살 종류 전환




public: // 화살 스폰 함수
	void Spawn_NormalArrowFunc();

	void Spawn_TeleportArrowFunc();

	void Spawn_FireArrowFunc();




	void SetLoadArrow_Load();

	void SetLoadArrow_Ready();


public:

	//===============
	// 플레이어 체력 -> 활에 UI
	// 남은 화살 갯수 ->활에서 화살에 UI


};
