// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackState.h"
#include "PlayerControllerBase.h"
#include "CharacterBase.h"
#include "AnimInstanceBase.h"
#include "Stat.h"
#include "Kismet/KismetSystemLibrary.h"


UAttackState::UAttackState() : AttackCount(0), IsAttacking(false),SaveAttack(false),bWeaponActive(false)
{
}

void UAttackState::Init(AController* pc, FVector atkSize)
{
	controller = pc;
	attackSize = atkSize;
}

void UAttackState::Init(AController* pc, FVector atkSize, UAnimMontage* montage)
{
	controller = pc;
	attackSize = atkSize;
	AttackMontages = montage;
}

void UAttackState::OnEnterState()
{
	APlayerControllerBase* APCB = GetPlayerControllerBase();
	ACharacterBase* ACP = CastChecked<ACharacterBase>(APCB->GetCharacter());
	UAnimInstanceBase* animBase = Cast<UAnimInstanceBase>(ACP->GetMesh()->GetAnimInstance());

	UStat* stat = ACP->stat;
	int32 atkCount = AttackCount++;

	if (atkCount == 0)
	{
		const FRotator Rotation = APCB->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		ACP->SetActorRotation(YawRotation);
	}

	animBase->Montage_Play(AttackMontages, stat->GetAtkSpeed());
	animBase->Montage_JumpToSection(FName(FString::FromInt(atkCount)), AttackMontages);
}

void UAttackState::OnTickState()
{
	if (bWeaponActive)
		OnAttack();
}

void UAttackState::OnExitState(ECreatureState post)
{
	SaveAttack = false;
	IsAttacking = false;
	WeaponAttackTargets.Empty();

	if (post == ECreatureState::Attack)
		return;
	AttackCount = 0;
}

// 오버드라이브 안하면 기본으로 쓸꺼
void UAttackState::OnAttack()
{
	APlayerControllerBase* APCB = GetPlayerControllerBase();
	ACharacterBase* ACP = CastChecked<ACharacterBase>(APCB->GetCharacter());
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
			UStat* targetStat = Actor->FindComponentByClass<UStat>();
			if (targetStat == nullptr)
				continue;

			//TODO
			if (WeaponAttackTargets.Contains(Actor) == false)
			{
				WeaponAttackTargets.Add(Actor);

				// 데미지 (나중에 구현)
				targetStat->OnAttacked(stat, EDamageType::Physical, 10.f);
			}
		}
	}
}
