// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MonsterFSM.h"
#include "AsyncTreeDifferences.h"
#include "ComponentSourceInterfaces.h"
#include "MonsterBase.h"
#include "NavigationInvokerComponent.h"
#include "NavigationSystem.h"
#include "Player_Archer.h"
#include "AI/MonsterAnim.h"
#include "Editor/VREditor/Private/UI/VREditorBaseUserWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Navigation/PathFollowingComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "StatesComponent.h"


UMonsterFSM::UMonsterFSM()
{

	PrimaryComponentTick.bCanEverTick = true;
	
	
	
}


// Called when the game starts
void UMonsterFSM::BeginPlay()
{
	Super::BeginPlay();

	// 나의 주인이 누군지 알거라.
	Self = Cast<AMonsterBase>(GetOwner());

	MonsterAnim = Cast<UMonsterAnim>(Self->GetMesh()->GetAnimInstance());

	// AI컨트롤러 생성
	Ai = Cast<AAIController>(Self->GetController());
	
}


// Called every frame
void UMonsterFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

	// 내상태 따라 각 일을 처리하고싶다.
	switch (State)
	{
	case EMonsterState::Idle:   TickIdle();    break;
	case EMonsterState::Move:   TickMove();    break;
	case EMonsterState::Attack: TickAttack();  break;
	case EMonsterState::Damage: TickDamage();  break;
	case EMonsterState::Die:    TickDie();	   break;
	}
}


bool UMonsterFSM::UpdateRandomLocation(FVector OldLoc, float Radius, FVector& NewLoc)
{
	// 네이게이션 시스템을 이용하여
	auto NS = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation Location;
	// 네비게이션 시스템 안에 랜덤으로 움직이는 함수를 가져와서 결과 값에 넣어주고
	bool Result = NS->GetRandomReachablePointInRadius(OldLoc,Radius,Location);
	// 랜덤위치가 정해지면
	if(Result == true)
	{
		// 그위치를 반환하고
		NewLoc = Location.Location;
		return true;
	}
	else
	{
		// 랜덤한위치를 찾지 못했을 때 재귀호출하여 다시 위치를 찾는다.
		return UpdateRandomLocation(OldLoc,Radius,NewLoc);
	}
	
}


void UMonsterFSM::TickIdle()
{
	//UE_LOG(LogTemp,Warning,TEXT("Idle!"))
	// 플레이어를 찾고 싶다, 목적지를 플레이어로 기억하고싶다.
	Target = Cast<APlayer_Archer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	// 만약 찾았다면 (조건)
	if(Target != nullptr)
	{
		// 이동 상태로 전이하고싶다.
		SetState(EMonsterState::Move); // 전이
	}

	
}

void UMonsterFSM::TickMove()
{
	//UE_LOG(LogTemp,Warning,TEXT("Move!"))
	// 목적지를 향해 이동하고싶다.
	FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	FVector Destination = Target->GetActorLocation();
	//Self->AddMovementInput(Direction.GetSafeNormal());

	// 타겟이 길위에 있다면
	// 네비게이션 시스템을 가져온다.
	UNavigationSystemV1* NS = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FPathFindingQuery Query;
	FAIMoveRequest Req;
	Req.SetAcceptanceRadius(50);
	Req.SetGoalLocation(Destination);
	// 요청하여 쿼리를 만드는 작업
	Ai->BuildPathfindingQuery(Req,Query);
	auto Result = NS->FindPathSync(Query);
	if(Result.IsSuccessful())
	{
		// 타겟을 향해서 이동하고싶다.
		Ai->MoveToLocation(Destination);
	
	}
	// 그렇지 않다면
	else
	{
		
		// Patrol 하고싶다.
		// 길 위에 랜덤한 위치를 하나 정해서 그곳으로 이동하고싶다.
		FPathFollowingRequestResult R;
		R.Code = Ai->MoveToLocation(RandomLocation);
		// 만약 그곳에 도착하거나 문제가 있다면 랜덤한 위치를 갱신하고 싶다.
		if(R!= EPathFollowingRequestResult::RequestSuccessful)
		{
			UpdateRandomLocation(Self->GetActorLocation(),500,RandomLocation);
		}
	}
	

	// 공격 가능 거리라면
	if(Direction.Length() <= AttackRange)
	{
		// 공격 상태로 전이하고싶다.
		SetState(EMonsterState::Attack);
		CurrentTime = AttackTime;
		Ai->StopMovement();
	}
	
	
}

void UMonsterFSM::TickAttack()
{
	//UE_LOG(LogTemp,Warning,TEXT("UMonsterFSM::TickAttack"));
	// Attack Wait
	CurrentTime += GetWorld()->GetDeltaSeconds();
	// 공격쿨타임이 되면
	if(CurrentTime > AttackTime)
	{
		// 공격 애니메이션을 키고
		MonsterAnim->IsAttack = true;
		CurrentTime = 0;
		float Dist = FVector::Dist(Target->GetActorLocation(), Self->GetActorLocation());
		// 공격범위를 벗어나면
		if(Dist > AttackRange)
		{
			// 타겟을 쫓고 쫓을 때는 공격하지 않도록 할것이다.
			SetState(EMonsterState::Move);
			MonsterAnim->IsAttack = false;
		}
		// 공격 범위를 벗어나지 않았으면
		else
		{
			Ai->SetFocus(Target,EAIFocusPriority::Gameplay);
			// 공격한다.
			//UE_LOG(LogTemp,Warning,TEXT("Attack!"));
		}
	}
}

void UMonsterFSM::TickDamage()
{
	
		// CurrentTime += GetWorld()->GetDeltaSeconds();
		// // 2초동안 대기 했다가
		// if(CurrentTime > DamageTime)
		// {
		// 	// 맞는 애니메이션을 하고
		// 	PlayMontageHit();
		// 	UE_LOG(LogTemp,Warning,TEXT("Hit!"));
		// 	// 이동상태로 전이 하고싶다.
		// 	SetState(EMonsterState::Move);
		// }
	
	
}

void UMonsterFSM::TickDie()
{
	if(false == MonsterAnim->IsDieDone)
	{
		return;
	}

	// 죽으면 콜리전 을 노콜리전은으로 바꾸고싶다.
	Self->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UE_LOG(LogTemp,Warning,TEXT("Hit!"));
	CurrentTime += GetWorld()->GetDeltaSeconds();
	if(CurrentTime>Dietime)
	{
			// 2초동안 대기 했다각
			// 이펙트를 작동하고 죽고싶다.
			Self->Destroy();
	}
	
	
}

void UMonsterFSM::PlayMontageHit()
{
	//Self->PlayAnimMontage(MonsterMontage,1,TEXT("Hit"));
	 FName SectionName = TEXT("Hit");
	 MonsterAnim->PlayMontageDamage(SectionName);
}

void UMonsterFSM::PlayMontageDie()
{
	//Self->PlayAnimMontage(MonsterMontage,1,TEXT("Died"));
	 FName SectionName = TEXT("Died");
	 MonsterAnim->PlayMontageDamage(SectionName);
}

void UMonsterFSM::OnchangeMoveState()
{
	SetState(EMonsterState::Move);
}

void UMonsterFSM::SetState(EMonsterState Next)
{
	// 만약 이동상태로 전이할때
	if(Next == EMonsterState::Move)
	{
		// 상대가 없으면 정찰모드로 돌아간다.
		UpdateRandomLocation(Self->GetActorLocation(),500,RandomLocation);

	}
	State = Next;
	MonsterAnim-> State = Next; 
	CurrentTime = 0;
}

