// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Skill/SpineDownState.h"
#include "CharacterBase.h"
#include "PlayerControllerBase.h"
#include "Stat.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AnimInstanceBase.h"
#include "StateMachineComponent.h"

USpineDownState::USpineDownState()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> loadMontage = ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("/Script/Engine.AnimMontage'/Game/Blueprints/Montage/Countess/AM_SpineDown.AM_SpineDown'"));
	if (loadMontage.Succeeded())
		montage = loadMontage.Object;

	DamageType = EDamageType::Physical;
}

bool USpineDownState::OnCheckEnterState()
{
	APlayerControllerBase* pcb = Cast<APlayerControllerBase>(GetPlayerControllerBase());
	ACharacterBase* cb = Cast<ACharacterBase>(pcb->GetCharacter());
	UStateMachineComponent* sm = cb->StateMachineComponent;
	UStat* stat = cb->stat;
	
	if (sm->EState == ECreatureState::Skill)
		return false;

	if (sm->GetCurrentState() == this)
		return false;

	// 하드 코딩
	return stat->GetCurMp() >= 10.f;
}

void USpineDownState::OnEnterState()
{
	APlayerControllerBase* pcb = Cast<APlayerControllerBase>(GetPlayerControllerBase());
	ACharacterBase* cb = Cast<ACharacterBase>(pcb->GetCharacter());
	UAnimInstanceBase* animBase = Cast<UAnimInstanceBase>(cb->GetMesh()->GetAnimInstance());
	UStat* stat = cb->stat;

	stat->SetCurMp(stat->GetCurMp() - 10.f);
	WeaponAttackTargets.Empty();
	// 몽타주 플레이
	animBase->Montage_Play(montage, stat->GetAtkSpeed());
	animBase->Montage_JumpToSection(FName(FString::FromInt(0)), montage);
}

void USpineDownState::OnExitState(ECreatureState post)
{
}

void USpineDownState::OnAttack()
{
	if (!bWeaponActive)
		return;

	APlayerControllerBase* APCB = GetPlayerControllerBase();
	ACharacterBase* ACP = CastChecked<ACharacterBase>(APCB->GetCharacter());
	UAnimInstanceBase* animBase = Cast<UAnimInstanceBase>(ACP->GetMesh()->GetAnimInstance());	
	FName index = animBase->Montage_GetCurrentSection();

	TArray<FHitResult> HitResults;
	FVector Center;

	if (index == "0")
	{
		Center = ACP->GetActorLocation();
		attackSize = FVector(100, 100, 100);
	}
	else if (index == "1")
	{
		Center = ACP->GetMesh()->GetSocketLocation(SocketName);
		attackSize = FVector(50, 50, 100);
	}

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
				targetStat->OnAttacked(stat, EDamageType::Physical, DamageLogic());
			}
		}
	}
}

float USpineDownState::DamageLogic()
{
	return 75.0f;
}
