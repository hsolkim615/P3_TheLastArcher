

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBoss.generated.h"

class USphereComponent;
class UMonsterBossFSM;

UCLASS()
class THELASTARCHER_API AMonsterBoss : public ACharacter
{
	GENERATED_BODY()

public:
	
	AMonsterBoss();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossSettings")
	USkeletalMeshComponent* SpawnStone;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossSettings")
	UMonsterBossFSM* BossFsm;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossSettings")
	USphereComponent* DamagePoint;
};
