// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterFSM.generated.h"

class APlayer_Archer;
class AMonsterBase;

UENUM(BlueprintType)
enum class EMonsterState
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
	float AttackRange = 300;
	

private:
	void TickIdle();
	void TickMove();
	void TickAttack();
	void TickDamage();
	void TickDie();
};
