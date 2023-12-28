// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow_Base.generated.h"

UCLASS()
class THELASTARCHER_API AArrow_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrow_Base();

	float ArrowSpeed = 1000.0f;

	bool bIsShotArrow = false;

	FVector ArrowDirection = GetActorForwardVector();

	FVector ArrowGoingDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* ArrowCollisionComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ArrowMeshComp;


	

	
};
