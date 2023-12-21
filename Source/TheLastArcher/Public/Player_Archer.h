// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	
	// 카메라
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	class UCameraComponent* CameraComp;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	class UStaticMeshComponent* HmdMesh;

	// 오른손
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	class UMotionControllerComponent* RightController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	class USkeletalMeshComponent* RightHand;

	// 왼손
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	class UMotionControllerComponent* LeftController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	class USkeletalMeshComponent* LeftHand;


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	class UInputMappingContext* imc;



};
