// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Base.h"
#include "IT_HealPotion.generated.h"

/**
 * 
 */
UCLASS()
class THELASTARCHER_API AIT_HealPotion : public AItem_Base
{
	GENERATED_BODY()

public:

	AIT_HealPotion();


	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;



};
