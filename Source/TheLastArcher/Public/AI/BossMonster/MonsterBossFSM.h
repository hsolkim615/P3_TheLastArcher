// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterBossFSM.generated.h"


class AMonsterBase;
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
	 Phase2,
	SpawnMonster,
	CastSpell,
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

	UPROPERTY(EditAnywhere,Category="BossMonsterSettings")
	float CurrentTime = 0;
	UPROPERTY(EditAnywhere,Category="BossMonsterSettings")
	float SkillCoolTime = 0;
	UPROPERTY(EditAnywhere,Category="BossMonsterSettings")
	float AttackTime = 5.0f;
	UPROPERTY(EditAnywhere,Category="BossMonsterSettings")
	float DieTime = 5.0f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossMonsterSettings")
	float SpawnTime = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossMonsterSettings")
	float FixedSpawnTime = 1;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABossMonsterProjectile> PRJClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABossSkullProjectile> SkullClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASpawnedSpell> SpellClass;

//=======~================================================================================================================================

	
private:
	void TickIdle();
	void TickThrow();
	void TickSpawnSkull();
	void TickDied();
	void Tickphase2();
	void TickSpawnMonster();
	void TickCastSpell();
	void SetState(EBossMonsterState Next);

public:
	void SpawnRock();
	void SpawnSkull();
	void SpawnSpell();

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
	
//=======~================================================================================================================================

public:
	UPROPERTY(EditAnywhere)
	TArray <AMonsterBase*> SummonedMonsters;
	
	UFUNCTION()
	bool IsAllDead();
	
	

};
