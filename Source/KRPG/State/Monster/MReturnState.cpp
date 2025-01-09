// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Monster/MReturnState.h"
#include "StateMachineComponent.h"
#include "MonsterAIControllerBase.h"
#include "CharacterMonster.h"

UMReturnState::UMReturnState()
{
}

void UMReturnState::OnEnterState()
{
	AMonsterAIControllerBase* mab = Cast<AMonsterAIControllerBase>(GetController());
	mab->CombatTarget = nullptr;
}

void UMReturnState::OnTickState()
{
	AMonsterAIControllerBase* mab = Cast<AMonsterAIControllerBase>(GetController());
	ACharacterMonster* cm = Cast<ACharacterMonster>(mab->GetCharacter());

	if (mab->InDestRange(mab->SpawnPos, 100.0f))
	{
		cm->StateMachineComponent->ChangeState(ECreatureState::Idle);
	}
	else
	{
		mab->MoveToPosition(mab->SpawnPos);
	}
}

void UMReturnState::OnExitState(ECreatureState post)
{
}
