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
	// ������ ==============
	// ī�޶�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UCameraComponent* CameraComp;

	// Hmd
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UStaticMeshComponent* HmdMesh;

	// ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UMotionControllerComponent* RightController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class USkeletalMeshComponent* RightHand;

	// �޼�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UMotionControllerComponent* LeftController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class USkeletalMeshComponent* LeftHand;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UInputMappingContext* InputMappingContext;


	// Ȱ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class USkeletalMeshComponent* BowMeshComp;

	// ������ ==============


public: // BindKey
	// ������ 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_RightThumbStick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_RightTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_RightGrip;



	// �޼� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_LeftThumbStick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_LeftTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_LeftGrip;




private: // Bind Function
	// �ʿ��� ����

	// �÷��̾��� �̵� ����
	FVector PlayerDirection;







	// ������ �Է�
	void RightThumbStick_Turn(const FInputActionValue& value); // �÷��̾� ������

	void RightThumbStick_Attack_Ready(const FInputActionValue& value); // �÷��̾� ���� - ȭ�� ��� 
	void RightThumbStick_Attack_Shot(const FInputActionValue& value); // �÷��̾� ���� - ȭ�� ����


	// �޼� �Է�
	void LeftThumbStick_Move(const FInputActionValue& value); // �÷��̾� �þ� ����

	void LeftTrigger_ReadyArrow(const FInputActionValue& value); // �÷��̾� ȭ�� ����








	//===============
	// �÷��̾� ü�� -> Ȱ�� UI
	// ���� ȭ�� ���� ->Ȱ���� ȭ�쿡 UI


};
