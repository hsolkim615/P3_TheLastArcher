// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoassSpellActor.generated.h"

class UCapsuleComponent;

UCLASS()
class THELASTARCHER_API ABoassSpellActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABoassSpellActor();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere,Category="BossSpell|Compontnt")
	UCapsuleComponent* CapsulComp;
	UPROPERTY(EditAnywhere,Category="BossSpell|Compontnt")
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
