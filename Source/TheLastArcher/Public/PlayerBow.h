// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerBow.generated.h"

UCLASS()
class THELASTARCHER_API APlayerBow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerBow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* BowSkeletalMesh;

	// ȭ�� ���� 3�� - �Ϲ� ȭ��, �ڷ���Ʈ ȭ��, ��ȭ��

};
