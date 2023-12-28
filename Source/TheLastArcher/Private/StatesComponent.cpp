


#include "StatesComponent.h"


UStatesComponent::UStatesComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100;
	CurrentHealth = MaxHealth;

	
}


// Called when the game starts
void UStatesComponent::BeginPlay()
{
	Super::BeginPlay();

	// 컴포넌트이기때문에 사용자를 부여하기 위하여 Owner를 만들어준다.
	AActor* Owner = GetOwner();
	// 만약 제대로 들어갔다면
	if(Owner)
	{
		// 데미지 받는 함수를 바인딩하자.(델리게이트)
		// 호출되면 함수 실행이된다.
		Owner->OnTakeAnyDamage.AddDynamic(this,&UStatesComponent::TakeDamage);
	}
}

void UStatesComponent::TakeDamage( AActor* DamagedActor, float Damage,
	const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	// 데미지가 음수 값이면 반영하지말고
	if(Damage <= 0)
	{
		IsDied = true;
		return;
	}
	// 데미지가 들어오면 CurrentHealth에서 데미지 값을 빼라.
	CurrentHealth = FMath::Clamp(CurrentHealth-Damage,0.0f,MaxHealth);
	IsDamaged = true;
}








