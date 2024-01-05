

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBoss.generated.h"

class UPlayer_DamageType;
class UBossMonsterState;
class UWidgetComponent;
class UStatesComponent;
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
//=======================================================================================================================================

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossSettings")
	UMonsterBossFSM* BossFsm;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossSettings")
	UBossMonsterState* StateComp;

//=======================================================================================================================================

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossSettings")
	USkeletalMeshComponent* SpawnStone;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossSettings")
	USphereComponent* DamagePoint;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossSettings")
	class UArrowComponent* SkullSpawn1;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossSettings")
	class UArrowComponent* SkullSpawn2;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossSettings")
	class UArrowComponent* SkullSpawn3;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossSettings")
	UArrowComponent* SpawnSpellpoint;

//=======================================================================================================================================

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossSettings")
	UWidgetComponent* HPcomponent;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossSettings")
	UStaticMeshComponent* WeekpointMeshComp;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="BossSettings")
	UCapsuleComponent* WeekpointCapsuleComp;
	UPlayer_DamageType* NormalDamage;

	//=======================================================================================================================================
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossSettings")
	float TakeDamage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BossSettings")
	float TakeMoreDamage;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
