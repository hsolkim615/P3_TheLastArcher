// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow_Type/Arrow_Normal.h"
#include "MonsterBase.h"


void AArrow_Normal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	
	if (OtherActor->IsA<AMonsterBase>()) {
		HitMonster = Cast<AMonsterBase>(OtherActor);

	}
}
