// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossMonsterAnim.generated.h"

enum class EBossMonsterState : uint8;
/**
 * 
 */
UCLASS()
class THELASTARCHER_API UBossMonsterAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossMonsterAnim")
	EBossMonsterState State;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossMonsterAnim")
	TObjectPtr<UAnimMontage> Throw;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossMonsterAnim")
	TObjectPtr<UAnimMontage> Spawn;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayMontageThrow(FName Section);

	
private:
	
	UFUNCTION()
	void AnimNotify_Throw();
	UFUNCTION()
	void AnimNotify_SpawnSkull();
};
