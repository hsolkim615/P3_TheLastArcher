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

class UStatesComponent;

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


	// ������ ==============


	// UI =====================================================
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UWidgetComponent* UI_PlayerHP;

	// 블루프린트에서 정의할 것
	UFUNCTION(BlueprintImplementableEvent)
	void SetCurrentPlayerHP(float MaxHP, float CurrentHP);



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

public:
	// �𸮾󿡼� ������ ȭ�� - ���� ���� �ʿ� ================
	UPROPERTY(EditAnywhere, Category = Spawn_ArrowType)
	TSubclassOf<class AArrow_Base> Factory_NomalArrow;

	UPROPERTY(EditAnywhere, Category = Spawn_ArrowType)
	TSubclassOf<class AArrow_Base> Factory_TeleportArrow;

	UPROPERTY(EditAnywhere, Category = Spawn_ArrowType)
	TSubclassOf<class AArrow_Base> Factory_FireArrow;
	// �𸮾󿡼� ������ ȭ�� - ���� ���� �ʿ� ================

	// ȭ�� ������ ��ġ 
	FTransform ArrowSpawnPlace;




	bool Choose_Normal = false;
	bool Choose_Teleport = false;
	bool Choose_Fire = false;

	bool GetItemFire = false;





private: // Bind Function
	// �ʿ��� ����

	// �÷��̾��� �̵� ����
	FVector PlayerDirection;

	// ������ ȭ�� ����
	bool bIsLoadArrow = false;

	// ���� ���� Arrow
	class AArrow_Base* LoadArrow;

	// ������ ������ ȭ��
	class AArrow_Base* GoArrow;

	FVector NewArrowPosition;


	bool bIsChangeArrow = true;




	// 오른손
	void RightThumbStick_Turn(const FInputActionValue& value); // �÷��̾� ������

	void RightTrigger_Attack_Ready(const FInputActionValue& value); // �÷��̾� ���� - ȭ�� ��� 
	void RightTrigger_Attack_Shot(const FInputActionValue& value); // �÷��̾� ���� - ȭ�� ����

	void RightGrip_TakeItem(const FInputActionValue& value); // �÷��̾� ���� - ȭ�� ����


	// 왼손
	void LeftThumbStick_Move(const FInputActionValue& value); // �÷��̾� �þ� ����

	void LeftTrigger_LoadArrow(const FInputActionValue& value); // �÷��̾� ȭ�� ����

	void LeftGrip_ChangeArrowType(const FInputActionValue& value); // �÷��̾� ȭ�� ���� ��ȯ
	void LeftGrip_ChangeArrow_Bool(const FInputActionValue& value); // �÷��̾� ȭ�� ���� ��ȯ




public: // ȭ�� ���� �Լ�
	void Spawn_NormalArrowFunc();

	void Spawn_TeleportArrowFunc();

	void Spawn_FireArrowFunc();




	void SetLoadArrow_Load();

	void SetLoadArrow_Ready();





public:

	//===============
	// �÷��̾� ü�� -> Ȱ�� UI
	// ���� ȭ�� ���� ->Ȱ���� ȭ�쿡 UI
	float PlayerHP = 100.f;

	UPROPERTY(EditAnywhere)
	UStatesComponent* StatesComp;

};
