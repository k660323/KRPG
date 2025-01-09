// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Monster/MIdleState.h"
#include "MonsterAIControllerBase.h"
#include "CharacterMonster.h"
#include "Perception/PawnSensingComponent.h"
#include "StateMachineComponent.h"
#include "Stat.h"

UMIdleState::UMIdleState()
{

}

void UMIdleState::OnEnterState()
{
	AMonsterAIControllerBase* mab = GetAIController();

	if (mab)
	{
		ACharacterMonster* cm = Cast<ACharacterMonster>(mab->GetCharacter());

		if (cm->pawnSensing)
			cm->pawnSensing->OnSeePawn.AddDynamic(this, &UMIdleState::PawnSeen);

		if (mab->CombatTarget)
		{
			if (mab->CombatTarget->StateMachineComponent->EState == ECreatureState::Die)
				mab->CombatTarget = nullptr;
			else if (mab->OutDestDistance(mab->SpawnPos, mab->MaxChaseDistance))
				cm->StateMachineComponent->ChangeState(ECreatureState::Return);
			else if (mab->InTargetRange(mab->CombatTarget, mab->atkRadius))
				cm->StateMachineComponent->ChangeState(ECreatureState::Attack);
			else
				cm->StateMachineComponent->ChangeState(ECreatureState::Chase);
		}

		if (mab->CombatTarget == nullptr)
		{
			controller->GetWorld()->GetTimerManager().SetTimer(ReturnTimer, FTimerDelegate::CreateLambda([this]() {
				// 3�ʵ� ������ ������ ���ư���
				AMonsterAIControllerBase* MACB = GetAIController();
				ACharacterMonster* cm = Cast<ACharacterMonster>(MACB->GetCharacter());
				if (MACB->CombatTarget == nullptr)
				{
					if (cm->StateMachineComponent->GetState(ECreatureState::Patrol))
					{
						// ���� ���� ���� ��ó�� ��Ʈ��
						cm->StateMachineComponent->ChangeState(ECreatureState::Patrol);
					}
					else
					{
						// ���� �ڸ��� ����
						cm->StateMachineComponent->ChangeState(ECreatureState::Return);
					}
				}
				}),
				FMath::RandRange(0.5f, 5.0f),
				false);
		}
	}
}

void UMIdleState::OnTickState()
{
}

void UMIdleState::OnExitState(ECreatureState post)
{
	AMonsterAIControllerBase* mab = Cast<AMonsterAIControllerBase>(GetController());
	ACharacterMonster* cm = Cast<ACharacterMonster>(mab->GetCharacter());

	controller->GetWorld()->GetTimerManager().ClearTimer(ReturnTimer);
	if (cm->pawnSensing)
		cm->pawnSensing->OnSeePawn.Clear();
}

void UMIdleState::PawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
		return;

	AMonsterAIControllerBase* mab = Cast<AMonsterAIControllerBase>(GetController());
	ACharacterMonster* cm = Cast<ACharacterMonster>(mab->GetCharacter());

	if (mab->CombatTarget == nullptr)
	{
		if (ACharacterBase* cb = Cast<ACharacterBase>(SeenPawn))
		{
			mab->CombatTarget = cb;

			// ���� �ൿ ����
			cm->StateMachineComponent->ChangeState(ECreatureState::Chase);
		}
	}
}
