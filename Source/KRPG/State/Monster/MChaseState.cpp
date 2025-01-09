// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Monster/MChaseState.h"
#include "StateMachineComponent.h"
#include "MonsterAIControllerBase.h"
#include "CharacterMonster.h"

UMChaseState::UMChaseState()
{
}

void UMChaseState::OnEnterState()
{

}

void UMChaseState::OnTickState()
{
	AMonsterAIControllerBase* mab = Cast<AMonsterAIControllerBase>(GetController());
	ACharacterMonster* cm = Cast<ACharacterMonster>(mab->GetCharacter());

	// 상대가 있다.
	if (mab->CombatTarget)
	{
		// 시작거리를 너무 벗어났으면 복귀
		if (mab->OutDestDistance(mab->SpawnPos, mab->MaxChaseDistance))
		{
			cm->StateMachineComponent->ChangeState(ECreatureState::Return);
		}
		// 공격범위 안에 있다.
		else if (mab->InTargetRange(mab->CombatTarget, mab->atkRadius))
		{
			// 공격 상태로 전환
			cm->StateMachineComponent->ChangeState(ECreatureState::Attack);
		}
		else
		{
			// 공격범위안에 없으면 닿을때까지 계속 따라간다
			mab->MoveToTarget(mab->CombatTarget);
		}
	}
	else
	{
		cm->StateMachineComponent->ChangeState(ECreatureState::Return);
	}

}

void UMChaseState::OnExitState(ECreatureState post)
{
	AMonsterAIControllerBase* MACB = GetAIController();
	MACB->StopMovement();

	if (post == ECreatureState::Return)
	{
		AMonsterAIControllerBase* mab = Cast<AMonsterAIControllerBase>(GetController());
		mab->CombatTarget = nullptr;
	}
}
