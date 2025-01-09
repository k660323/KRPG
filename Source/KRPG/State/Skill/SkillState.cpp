// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Skill/SkillState.h"
#include "CharacterBase.h"
#include "PlayerControllerBase.h"
#include "Stat.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AnimInstanceBase.h"
#include "StateMachineComponent.h"


USkillState::USkillState()
{
	SocketName = "AttackDefault";
	attackSize = FVector(5, 5, 5);
}

void USkillState::OnTickState()
{
	OnAttack();
}

void USkillState::OnAttack()
{
	if (!bWeaponActive)
		return;

	APlayerControllerBase* APCB = GetPlayerControllerBase();
	ACharacterBase* ACP = CastChecked<ACharacterBase>(APCB->GetCharacter());
	FVector Center = ACP->GetMesh()->GetSocketLocation(SocketName);

	TArray<FHitResult> HitResults;

	bool bSuccess = UKismetSystemLibrary::BoxTraceMulti(ACP,
		Center,
		Center,
		attackSize,
		ACP->GetActorRotation(),
		ETraceTypeQuery::TraceTypeQuery3,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForDuration,
		OUT  HitResults,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		1.f
	);

	if (bSuccess)
	{
		UStat* stat = ACP->stat;

		for (FHitResult& HitResult : HitResults)
		{
			AActor* Actor = HitResult.GetActor();
			if (Actor == nullptr)
				continue;
			UStat* targetStat = Actor->FindComponentByClass<UStat>();
			if (targetStat == nullptr)
				continue;

			//TODO
			if (WeaponAttackTargets.Contains(Actor) == false)
			{
				WeaponAttackTargets.Add(Actor);

				// 데미지 (나중에 구현)
				targetStat->OnAttacked(stat, DamageType, DamageLogic());
			}
		}
	}
}
