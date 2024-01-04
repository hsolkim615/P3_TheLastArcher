// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "BossSkullProjectile.generated.h"


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
	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		

	

};
