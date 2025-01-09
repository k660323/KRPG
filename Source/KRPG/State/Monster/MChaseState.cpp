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

	// ��밡 �ִ�.
	if (mab->CombatTarget)
	{
		// ���۰Ÿ��� �ʹ� ������� ����
		if (mab->OutDestDistance(mab->SpawnPos, mab->MaxChaseDistance))
		{
			cm->StateMachineComponent->ChangeState(ECreatureState::Return);
		}
		// ���ݹ��� �ȿ� �ִ�.
		else if (mab->InTargetRange(mab->CombatTarget, mab->atkRadius))
		{
			// ���� ���·� ��ȯ
			cm->StateMachineComponent->ChangeState(ECreatureState::Attack);
		}
		else
		{
			// ���ݹ����ȿ� ������ ���������� ��� ���󰣴�
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
