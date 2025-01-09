// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Skill/CrossSlashState.h"
#include "CharacterBase.h"
#include "PlayerControllerBase.h"
#include "Stat.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AnimInstanceBase.h"
#include "StateMachineComponent.h"

UCrossSlashState::UCrossSlashState()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> loadMontage = ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("/Script/Engine.AnimMontage'/Game/Blueprints/Montage/Countess/AM_CrossSlash.AM_CrossSlash'"));
	if (loadMontage.Succeeded())
		montage = loadMontage.Object;

	attackSize = FVector(100, 100, 100);
	DamageType = EDamageType::Physical;
}

bool UCrossSlashState::OnCheckEnterState()
{
	APlayerControllerBase* pcb = Cast<APlayerControllerBase>(GetPlayerControllerBase());
	ACharacterBase* cb = Cast<ACharacterBase>(pcb->GetCharacter());
	UStateMachineComponent* sm = cb->StateMachineComponent;
	UStat* stat = cb->stat;

	if (sm->EState == ECreatureState::Skill)
		return false;

	if (cb->StateMachineComponent->GetCurrentState() == this)
		return false;

	// 하드 코딩
	return stat->GetCurMp() >= 30.f;
}

void UCrossSlashState::OnEnterState()
{
	APlayerControllerBase* pcb = Cast<APlayerControllerBase>(GetPlayerControllerBase());
	ACharacterBase* cb = Cast<ACharacterBase>(pcb->GetCharacter());
	UAnimInstanceBase* animBase = Cast<UAnimInstanceBase>(cb->GetMesh()->GetAnimInstance());
	UStat* stat = cb->stat;

	stat->SetCurMp(stat->GetCurMp() - 30.f);
	WeaponAttackTargets.Empty();
	// 몽타주 플레이
	animBase->Montage_Play(montage, stat->GetAtkSpeed());
	animBase->Montage_JumpToSection(FName(FString::FromInt(1)), montage);
}

void UCrossSlashState::OnExitState(ECreatureState post)
{
}

float UCrossSlashState::DamageLogic()
{
	return 100.0f;
}
