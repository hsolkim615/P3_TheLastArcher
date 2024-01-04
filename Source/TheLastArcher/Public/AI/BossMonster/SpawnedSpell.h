

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpawnedSpell.generated.h"

class APlayer_Archer;

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

	

	UStaticMeshComponent* MeshComp;

	float CurrentTime;
	float CastTime = 10.0f;
	float Damag = 100;

	UPROPERTY(EditAnywhere,Category="BossSettings")
	class UPlayer_DamageType* NormalDamage;

	UPROPERTY(EditAnywhere)
	APlayer_Archer* Target;
	
	UFUNCTION(BlueprintCallable)
	void TakeDamage( AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
