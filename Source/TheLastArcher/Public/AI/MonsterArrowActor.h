// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterArrowActor.generated.h"

class UPlayer_DamageType;
class UProjectileMovementComponent;
class UCapsuleComponent;

UCLASS()
class THELASTARCHER_API AMonsterArrowActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AMonsterArrowActor();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Arrow;
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Speed = 30000;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Damage = 10.f;
	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	UPlayer_DamageType* NomalDamge;

};
