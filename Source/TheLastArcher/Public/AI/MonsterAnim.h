// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterFSM.h"
#include "MonsterAnim.generated.h"

/**
 * 
 */
UCLASS()
class THELASTARCHER_API UMonsterAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMonsterState State;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsAttack;
};
