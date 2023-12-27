// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_Archer.h"
#include "Components/ActorComponent.h"
#include "Framework/Docking/STabDrawer.h"
#include "MonsterFSM.generated.h"


class UMonsterAnim;
class UNormalMonsterAnimInstance;
class APlayer_Archer;
class AMonsterBase;

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELASTARCHER_API UMonsterFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMonsterFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMonsterState State;
	// FSM Owner 설정
	UPROPERTY()
	AMonsterBase* Self;

	UPROPERTY()
	APlayer_Archer* Target;

	// 공격 가능거리
	UPROPERTY(EditAnywhere)
	float AttackRange;

	float CurrentTime;
	// 경직
	UPROPERTY(EditAnywhere)
	float DamageTime = 2;
	UPROPERTY(EditAnywhere)
	float Dietime = 2;
	// 공격 쿨타임
	UPROPERTY(EditAnywhere)
	float AttackTime = 2;
	
	
public:
	void SetState(EMonsterState Next);

private:
	
	void TickIdle();
	void TickMove();
	void TickAttack();
	void TickDamage();
	void TickDie();

public:
	UPROPERTY()
	UMonsterAnim* MonsterAnim;

	UPROPERTY(EditAnywhere)
	UAnimMontage* MonsterMontage;

	// 맞는 애니메이션
	void PlayMontageHit();
	// 죽는 애니메이션
	void PlayMontageDie();
	
	
};
