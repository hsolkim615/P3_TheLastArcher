// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Player_Archer.generated.h"

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




private: // Bind Function
	// 필요한 변수

	// 플레이어의 이동 방향
	FVector PlayerDirection;







	// 오른손 입력
	void RightThumbStick_Turn(const FInputActionValue& value); // 플레이어 움직임

	void RightThumbStick_Attack_Ready(const FInputActionValue& value); // 플레이어 공격 - 화살 잡기 
	void RightThumbStick_Attack_Shot(const FInputActionValue& value); // 플레이어 공격 - 화살 놓기


	// 왼손 입력
	void LeftThumbStick_Move(const FInputActionValue& value); // 플레이어 시야 각도

	void LeftTrigger_ReadyArrow(const FInputActionValue& value); // 플레이어 화살 장전








	//===============
	// 플레이어 체력 -> 활에 UI
	// 남은 화살 갯수 ->활에서 화살에 UI


};
