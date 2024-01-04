// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase.generated.h"

class UWidgetComponent;
class UMonsterSwordComponent;
class URangerMonsterFSM;
class UStatesComponent;
class UNavigationInvokerComponent;
class UMonsterFSM;
class USkeletalMeshComponent;

UCLASS()
class THELASTARCHER_API AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UMonsterFSM> MonsterFsmClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMonsterFSM* MonsterFsm;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UWidgetComponent* HPComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStatesComponent* HP;

	UPROPERTY(EditAnywhere)
	UArrowComponent* ArrowComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USkeletalMeshComponent* Weapon;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UCapsuleComponent* WeaponCapsuleComp;

	// 블루프릔트에서 UI에 연동시키기 위한 함수 선언.
	// UFUNCTION(BlueprintImplementableEvent)
	// void DamgeUpdateUI(float CurrentHp, float MaxHp);

	
	
};
