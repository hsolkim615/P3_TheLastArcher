// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "BossSkullProjectile.generated.h"


class UPlayer_DamageType;
class UProjectileMovementComponent;
class AMonsterBoss;
class APlayer_Archer;
class USphereComponent;

UCLASS()

class THELASTARCHER_API ABossSkullProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABossSkullProjectile();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossSettings")
	USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossSettings")
	UStaticMeshComponent* MeshComp;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossSettings")
	APlayer_Archer* Target;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossSettings")
	AMonsterBoss* Self;

	UPROPERTY(EditAnywhere,Category="BossSettings")
	float Speed = 1500;

	UPROPERTY(EditAnywhere,Category="BossSettings")
	float Damage = 20;

	UPROPERTY(EditAnywhere,Category="BossSettings")
	UPlayer_DamageType* NormalDamage;

	bool IsHit = false;

	bool CheckHit();
	
	UPROPERTY()
	FTimerHandle TimerHandle_FindTarget;
	// 위치를 계속 최신화 하는 함수를 만든다.
	void FindTarget();
	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		

	

};
