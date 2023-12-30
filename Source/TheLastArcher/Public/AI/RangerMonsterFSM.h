// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/MonsterFSM.h"
#include "RangerMonsterFSM.generated.h"

/**
 * 
 */
UCLASS()
class THELASTARCHER_API URangerMonsterFSM : public UMonsterFSM
{
	GENERATED_BODY()

	URangerMonsterFSM();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void TickAttack() override;

	virtual void PlayMontageHit() override;

	virtual void PlayMontageDie() override;
	
	
	void SpawnArrow();

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SpawnArrow")
	TSubclassOf<class AMonsterArrowActor> ArrowClass;
private:
	UPROPERTY()
	float RangeAttackTime = 3.0f;
	
};
