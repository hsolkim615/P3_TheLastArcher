

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpawnedSpell.generated.h"

class AMonsterBoss;
class USphereComponent;
class APlayer_Archer;
class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS()
class THELASTARCHER_API ASpawnedSpell : public ACharacter
{
	GENERATED_BODY()

public:
	
	ASpawnedSpell();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComp;;
	
	// UPROPERTY(EditAnywhere)
	// UStaticMeshComponent* MeshComp;
	

	float CurrentTime = 0;
	float Time = 0;
	float CastTime = 10.0f;
	float Damag = 100;
	int32 MaxCount = 2;
	int32 Count = 0;
	float WeekTime = 5.0f;

	UPROPERTY(EditAnywhere,Category="BossSettings")
	class UPlayer_DamageType* NormalDamage;

	UPROPERTY(EditAnywhere)
	APlayer_Archer* Target;

	UPROPERTY(EditAnywhere)
	AMonsterBoss* Boss;
		
	

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
