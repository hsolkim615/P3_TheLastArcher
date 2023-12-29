// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "Player_DamageType.generated.h"

/**
 * 
 */
UCLASS()
class THELASTARCHER_API UPlayer_DamageType : public UDamageType
{
	GENERATED_BODY()
	
public:
    UPlayer_DamageType();

};

UCLASS()
class THELASTARCHER_API UNormalArrow_Type : public UDamageType
{
	GENERATED_BODY()
	
public:
    UNormalArrow_Type();
   

    //void OnArrowHit(AActor* DamagedActor, float DamageAmount);
    


};