// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Monster/MHitState.h"
#include "CharacterMonster.h"
#include "MonsterAIControllerBase.h"
#include "AnimInstanceBase.h"

UMHitState::UMHitState()
{
}

void UMHitState::Init(AController* pc, UAnimMontage* montages)
{
	controller = pc;
	montage = montages;
}

void UMHitState::OnEnterState()
{
	AMonsterAIControllerBase* MAB = Cast<AMonsterAIControllerBase>(GetAIController());
	ACharacterMonster* cm = Cast<ACharacterMonster>(MAB->GetCharacter());
	UAnimInstanceBase* ab = Cast<UAnimInstanceBase>(cm->GetMesh()->GetAnimInstance());
	// 몽타주 플레이
	ab->Montage_Play(montage, 1.0f);
}

void UMHitState::OnTickState()
{
}

void UMHitState::OnExitState(ECreatureState post)
{
}
