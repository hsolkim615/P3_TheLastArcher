// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arrow_Base.h"
#include "Arrow_Normal.generated.h"

/**
 * 
 */
UCLASS()
class THELASTARCHER_API AArrow_Normal : public AArrow_Base
{
	GENERATED_BODY()

public:
	AArrow_Normal();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float Damage;



};
