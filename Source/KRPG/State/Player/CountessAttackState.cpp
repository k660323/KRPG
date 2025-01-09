// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Player/CountessAttackState.h"
#include "../ControllerEx/Player/PlayerControllerBase.h"
#include "CharacterBase.h"
#include "AnimInstanceBase.h"
#include "Stat.h"
#include "Kismet/KismetSystemLibrary.h"

UCountessAttackState::UCountessAttackState()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> atkMontage = ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("/Script/Engine.AnimMontage'/Game/Blueprints/Montage/Countess/AM_Attack.AM_Attack'"));
	if (atkMontage.Succeeded())
		AttackMontages = atkMontage.Object;
}

void UCountessAttackState::OnAttack()
{
	if (!bWeaponActive)
		return;

	APlayerControllerBase* APB = GetPlayerControllerBase();
	ACharacterBase* ACP = CastChecked<ACharacterBase>(APB->GetCharacter());

	FVector Start;
	FVector End;
	bool bSuccess = false;
	TArray<FHitResult> HitResults;

	Start = ACP->GetMesh()->GetSocketLocation(FName("AttackDefault"));
	End = ACP->GetMesh()->GetSocketLocation(FName("AttackDefault"));

	bSuccess = UKismetSystemLibrary::BoxTraceMulti(ACP,
		Start,
		End,
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
		3.f
	);
	/*
	switch (AttackCount)
	{
	case 1:
		Start = ACP->GetMesh()->GetSocketLocation(FName("AttackStartR"));
		End = ACP->GetMesh()->GetSocketLocation(FName("AttackEndR"));
		bSuccess = UKismetSystemLibrary::SphereTraceMulti(ACP,
			Start,
			End,
			12.f,
			ETraceTypeQuery::TraceTypeQuery3,
			false,
			TArray<AActor*>(),
			EDrawDebugTrace::ForDuration,
			OUT  HitResults,
			true,
			FLinearColor::Red,
			FLinearColor::Green,
			1.f);
		break;
	case 2:
		Start = ACP->GetMesh()->GetSocketLocation(FName("AttackStartL"));
		End = ACP->GetMesh()->GetSocketLocation(FName("AttackEndL"));
		bSuccess = UKismetSystemLibrary::SphereTraceMulti(ACP,
			Start,
			End,
			12.f,
			ETraceTypeQuery::TraceTypeQuery3,
			false,
			TArray<AActor*>(),
			EDrawDebugTrace::ForDuration,
			OUT  HitResults,
			true,
			FLinearColor::Red,
			FLinearColor::Green,
			1.f);
		break;
	case 3:
		Start = ACP->GetMesh()->GetSocketLocation(FName("AttackDefault"));
		End = ACP->GetMesh()->GetSocketLocation(FName("AttackDefault"));

		bSuccess = UKismetSystemLibrary::BoxTraceMulti(ACP,
			Start,
			End,
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
			3.f
		);
		break;
	}
	*/

	if (bSuccess)
	{
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

				// µ¥¹ÌÁö
				targetStat->OnAttacked(ACP->stat, EDamageType::Physical, 50.f);
			}
		}
	}
}
