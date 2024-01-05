

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BossMonsterState.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELASTARCHER_API UBossMonsterState : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UBossMonsterState();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurrentHealth;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Phase2 = 700;

	void UpdateHP(float UpdatedHealth);
	
	UFUNCTION(BlueprintCallable)
	void TakeDamage( AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
