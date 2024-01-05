// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_DamageType.h"
#include "GameFramework/Actor.h"
#include "BossMonsterProjectile.generated.h"

class AMonsterBoss;
class APlayer_Archer;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class THELASTARCHER_API ABossMonsterProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossMonsterProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	APlayer_Archer* Target;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AMonsterBoss* Self;
	UPROPERTY(EditAnywhere,Category="PorjectileSettings")
	USphereComponent* SphereComp;	
	UPROPERTY(EditAnywhere,Category="PorjectileSettings")
	UStaticMeshComponent* MeshComp;
	UPROPERTY(EditAnywhere,Category="PorjectileSettings")
	UProjectileMovementComponent* PRJComp;

	UPROPERTY(EditAnywhere,Category="PorjectileSettings")
	float Speed = 1000;

	UPROPERTY()
	UPlayer_DamageType* NormalDamage;
private:
	float Damage = 20;
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
