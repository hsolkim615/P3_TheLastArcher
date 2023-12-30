// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELASTARCHER_API UStatesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UStatesComponent();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurrentHealth;
	
	void UpdateHP(float UpdatedHealth);
	
	// UFUNCTION(BlueprintCallable)
	// void TakeDamage( AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor,float Damage);
	
};
