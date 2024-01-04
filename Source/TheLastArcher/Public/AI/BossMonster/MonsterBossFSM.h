// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterBossFSM.generated.h"


class UBossMonsterAnim;
class AAIController;
class APlayer_Archer;
class AMonsterBoss;

UENUM(BlueprintType)
enum class EBossMonsterState : uint8
{
	Idle,
	Throw,
	SpawnSkull,
	Died,
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELASTARCHER_API UMonsterBossFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UMonsterBossFSM();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//=======~================================================================================================================================

public:
	APlayer_Archer* Target;
	AMonsterBoss* Self;
	AAIController* AI;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossMonsterSettings")
	EBossMonsterState State;
//=======~================================================================================================================================

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossMonsterSettings")
	float CurrentTime;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossMonsterSettings")
	float SkillCoolTime;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossMonsterSettings")
	float AttackTime = 3.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossMonsterSettings")
	float SkillTime = 10.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABossMonsterProjectile> PRJClass;

//=======~================================================================================================================================

	
private:
	void TickIdle();
	void TickThrow();
	void TickSpawnSkull();
	void TickDied();
	void SetState(EBossMonsterState Next);

public:
	void SpawnRock();
	void SpawnSkull();
//=======~================================================================================================================================

private:
	UPROPERTY()
	UBossMonsterAnim* BossMonsterAnim;

public:
	//newcode
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category ="Boss")
	UAnimMontage* AM_BossAction;
	
	UFUNCTION()
	void OnThrowMontageEnded(UAnimMontage* Montage,bool bInterrupted);
};
