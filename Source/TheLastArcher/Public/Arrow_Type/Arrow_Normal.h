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

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	
};
