// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Skill/UltimateSkillState.h"
#include "CharacterBase.h"
#include "PlayerControllerBase.h"
#include "Stat.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AnimInstanceBase.h"
#include "StateMachineComponent.h"

UUltimateSkillState::UUltimateSkillState()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> loadMontage = ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("/Script/Engine.AnimMontage'/Game/Blueprints/Montage/Countess/AM_Ultimate.AM_Ultimate'"));
	if (loadMontage.Succeeded())
		montage = loadMontage.Object;

	attackSize = FVector(100, 100, 100);
	DamageType = EDamageType::Physical;
}

bool UUltimateSkillState::OnCheckEnterState()
{
	APlayerControllerBase* pcb = Cast<APlayerControllerBase>(GetPlayerControllerBase());
	ACharacterBase* cb = Cast<ACharacterBase>(pcb->GetCharacter());
	UStat* stat = cb->stat;

	if (cb->StateMachineComponent->GetCurrentState() == this)
		return false;

	// 하드 코딩
	return stat->GetCurMp() >= 50.f;
}

void UUltimateSkillState::OnEnterState()
{
	APlayerControllerBase* pcb = Cast<APlayerControllerBase>(GetPlayerControllerBase());
	ACharacterBase* cb = Cast<ACharacterBase>(pcb->GetCharacter());
	UAnimInstanceBase* animBase = Cast<UAnimInstanceBase>(cb->GetMesh()->GetAnimInstance());
	UStat* stat = cb->stat;

	stat->SetCurMp(stat->GetCurMp() - 50.f);
	WeaponAttackTargets.Empty();
	// 몽타주 플레이
	animBase->Montage_Play(montage, stat->GetAtkSpeed());
	animBase->Montage_JumpToSection(FName(FString::FromInt(1)), montage);
}

void UUltimateSkillState::OnExitState(ECreatureState post)
{
}


float UUltimateSkillState::DamageLogic()
{
	return 500.0f;
}
