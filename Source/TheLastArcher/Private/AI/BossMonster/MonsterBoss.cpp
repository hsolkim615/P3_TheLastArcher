


#include "AI/BossMonster/MonsterBoss.h"

#include "Arrow_Base.h"
#include "Player_Archer.h"
#include "Player_DamageType.h"
#include "StatesComponent.h"
#include "AI/BossMonsterState.h"
#include "AI/BossMonster/MonsterBossFSM.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"



AMonsterBoss::AMonsterBoss()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
//=======~================================================================================================================================
	BossFsm = CreateDefaultSubobject<UMonsterBossFSM>("BossFSM");

	StateComp = CreateDefaultSubobject<UBossMonsterState>("StateComp");
	
//=======~================================================================================================================================
	// Mesh를 가져온다.
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshTemp(TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/BossMonster/Model/BossMonster.BossMonster_C'"));
	if(MeshTemp.Succeeded())
	{
		GetMesh()->SetRelativeLocationAndRotation(FVector(0,0,-90),FRotator(0,0,-90));
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetRelativeScale3D(FVector(100,100,100));
	}
	
//=======~================================================================================================================================
	// 돌이 소환 되는 위치를 정한다.
	SpawnStone = CreateDefaultSubobject<USkeletalMeshComponent>("SpawnStone");
	SpawnStone -> SetupAttachment(GetMesh(),"SpawnPoint");
	SpawnStone -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
//=======~================================================================================================================================

	// 머리 쪽에 1페이지 타격이 가능한 컴퍼넌트를 만든다.
	DamagePoint = CreateDefaultSubobject<USphereComponent>("DamagePoint");
	DamagePoint -> SetupAttachment(GetMesh(),"DamageSocket");
	//(X=0.000000,Y=0.500000,Z=1.000000)
	DamagePoint -> SetRelativeLocation(FVector(0,0.5f,1.0f));
	DamagePoint -> SetRelativeScale3D(FVector(0.04f));
	
//=======~================================================================================================================================

	// 해골이 소환 되는 위치를 잡아주는 에로우 컴퍼넌트를 만든다.
	SkullSpawn1 = CreateDefaultSubobject<UArrowComponent>("SkullSpawn1");
	SkullSpawn1 -> SetRelativeLocation(FVector(0,660.f,550.f));
	SkullSpawn1 ->SetupAttachment(RootComponent);
	SkullSpawn2 = CreateDefaultSubobject<UArrowComponent>("SkullSpawn2");
	SkullSpawn2 -> SetRelativeLocation(FVector(0,-930.f,380.f));
	SkullSpawn2 ->SetupAttachment(RootComponent);

	SkullSpawn3 = CreateDefaultSubobject<UArrowComponent>("SkullSpawn3");
	SkullSpawn3 -> SetRelativeLocation(FVector(0,0,780.f));
	SkullSpawn3 -> SetupAttachment(RootComponent);

//=======~================================================================================================================================
	

	HPcomponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPComponent"));
	HPcomponent->SetupAttachment(RootComponent);
	ConstructorHelpers::FClassFinder<UUserWidget>TempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/TheLastArchers/KSE/Blueprints/UI/WBP_BothHealthBar.WBP_BothHealthBar_C'"));
	if(TempWidget.Succeeded())
	{
		HPcomponent->SetWidgetClass(TempWidget.Class);
		HPcomponent->SetDrawSize(FVector2D(2000.f,20.f));
		HPcomponent->SetRelativeLocation(FVector(0,0,890));
		HPcomponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	UCapsuleComponent* Cap = GetCapsuleComponent();
	auto Meshc = GetMesh();
	Cap->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	Cap->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);

	Meshc->SetCollisionResponseToChannel(ECC_Visibility,ECR_Ignore);
	Meshc->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);

//=======~================================================================================================================================

	WeekpointMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("WeekpointMeshComp");
	WeekpointMeshComp->SetupAttachment(GetMesh(),"WeekPoint");
	// 약점을 단다.
	ConstructorHelpers::FObjectFinder<UStaticMesh>TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Resource/BossWP/Mine/Crystal_Crystal_003_low.Crystal_Crystal_003_low'"));
	if(TempMesh.Succeeded())
	{
		WeekpointMeshComp->SetStaticMesh(TempMesh.Object);
		//(X=3.000000,Y=0.000000,Z=0.100000)
		//(Pitch=0.000000,Yaw=0.000000,Roll=-170.000000)
		WeekpointMeshComp->SetRelativeLocationAndRotation(FVector(3.0f,0,0.1f),FRotator(0,0,-170));
		//(X=0.100000,Y=0.100000,Z=0.100000)
		WeekpointMeshComp->SetRelativeScale3D(FVector(0.1f));
		WeekpointMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	WeekpointCapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("WeekpointCapsuleComp");
	WeekpointCapsuleComp -> SetupAttachment(WeekpointMeshComp);
	//(X=-37.000000,Y=-3.000000,Z=20.000000)
	//(Pitch=30.000000,Yaw=5.000000,Roll=191.000000)
	WeekpointCapsuleComp -> SetRelativeLocationAndRotation(FVector(-37.0f,-3.0f,20.0f),FRotator(30,5,191));
	//(X=1.000000,Y=1.000000,Z=1.000000)
	WeekpointCapsuleComp -> SetRelativeScale3D(FVector(1.0f));
	WeekpointCapsuleComp->SetCapsuleHalfHeight(17.8f);
	WeekpointCapsuleComp->SetCapsuleRadius(8.2f);

//=======~================================================================================================================================

	SpawnSpellpoint = CreateDefaultSubobject<UArrowComponent>("SpawnSpellpoint");
	SpawnSpellpoint -> SetupAttachment(RootComponent);
	//(X=920.000000,Y=0.000000,Z=0.000000)
	SpawnSpellpoint -> SetRelativeLocation(FVector(920,0,210));
	
}	




void AMonsterBoss::BeginPlay()
{
	Super::BeginPlay();
	DamagePoint->OnComponentBeginOverlap.AddDynamic(this,&AMonsterBoss::OverlapBegin);
	WeekpointCapsuleComp->OnComponentBeginOverlap.AddDynamic(this,&AMonsterBoss::OverlapBegin);
}


void AMonsterBoss::Tick(float DeltaTime)
{
	// 체력바 UI 빌보드처리
	Super::Tick(DeltaTime);
	FVector Start = HPcomponent->GetComponentLocation() ;
	FVector Target = UGameplayStatics::GetPlayerCameraManager(GetWorld(),0)->GetCameraLocation();;
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(Start,Target);
	HPcomponent->SetWorldRotation(NewRotation);

	
}


void AMonsterBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonsterBoss::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 부딪힌 대상이 화살인지 체크
	 auto Arrow = Cast<AArrow_Base>(OtherActor);
	if(Arrow != nullptr)
	{
		// 부딪힌 대상이 얼굴이라면.
		if(OverlappedComponent == DamagePoint)
		{
			
			this->StateComp->TakeDamage(this,TakeDamage,NormalDamage,nullptr,OtherActor);	
		}
		else if(OverlappedComponent == WeekpointCapsuleComp)
		{
			this->StateComp->TakeDamage(this,TakeMoreDamage,NormalDamage,nullptr,OtherActor);
		}
		
	}
}

