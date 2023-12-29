// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterArrowActor.generated.h"

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

	float Speed = 800;
	float Damage = 10;
	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
