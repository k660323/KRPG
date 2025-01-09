// Fill out your copyright notice in the Description page of Project Settings.


#include "MAttackState.h"
#include "MonsterAIControllerBase.h"
#include "CharacterBase.h"
#include "CharacterMonster.h"
#include "AnimInstanceBase.h"
#include "Stat.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Util.h"
#include <Define.h>

UMAttackState::UMAttackState()
{

}

void UMAttackState::Init(AController* pc, FVector atkSize)
{
	controller = pc;
	attackSize = atkSize;
}

void UMAttackState::Init(AController* pc, FVector atkSize, UAnimMontage* montage)
{
	controller = pc;
	attackSize = atkSize;
	AttackMontages = montage;
}

void UMAttackState::OnEnterState()
{
	AMonsterAIControllerBase* AMACB = GetAIController();
	ACharacterBase* ACP = CastChecked<ACharacterBase>(AMACB->GetCharacter());
	UAnimInstanceBase* animBase = Cast<UAnimInstanceBase>(ACP->GetMesh()->GetAnimInstance());

	UStat* stat = ACP->stat;
	int32 atkCount = AttackCount++;

	if (atkCount == 0)
	{
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(ACP->GetActorLocation(), AMACB->CombatTarget->GetActorLocation());
		ACP->SetActorRotation(FRotator(0, Rotation.Yaw, 0));
		//FRotator Rotation = UUtil::LookAt(ACP, AMACB->CombatTarget);
		//ACP->AddActorWorldRotation(FRotator(0, Rotation.Yaw, 0));
	}

	animBase->Montage_Play(AttackMontages, stat->GetAtkSpeed());
	animBase->Montage_JumpToSection(FName(FString::FromInt(atkCount)), AttackMontages);
}

void UMAttackState::OnTickState()
{
	if (bWeaponActive)
		OnAttack();
}

void UMAttackState::OnExitState(ECreatureState post)
{	
	SaveAttack = false;
	IsAttacking = false;
	WeaponAttackTargets.Empty();

	if (post == ECreatureState::Attack)
		return;

	AttackCount = 0;
}

void UMAttackState::OnAttack()
{
	AMonsterAIControllerBase* AMACB = GetAIController();
	ACharacterBase* ACP = CastChecked<ACharacterBase>(AMACB->GetCharacter());
	FVector Center = ACP->GetMesh()->GetSocketLocation(FName("AttackDefault"));

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

			if (Cast<ACharacterMonster>(Actor))
				continue;

			UStat* targetStat = Actor->FindComponentByClass<UStat>();
			if (targetStat == nullptr)
				continue;
			
			//TODO
			if (WeaponAttackTargets.Contains(Actor) == false)
			{
				WeaponAttackTargets.Add(Actor);

				// 데미지 (나중에 구현)
				targetStat->OnAttacked(stat,EDamageType::Physical, 10.f);
			}
		}
	}
}