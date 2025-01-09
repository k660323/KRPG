// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Monster/MPatrolState.h"
#include "CharacterMonster.h"
#include "MonsterAIControllerBase.h"
#include "StateMachineComponent.h"
#include "Perception/PawnSensingComponent.h"

UMPatrolState::UMPatrolState()
{
}

void UMPatrolState::OnEnterState()
{
	AMonsterAIControllerBase* MACB = GetAIController();
	ACharacterMonster* cm = Cast<ACharacterMonster>(MACB->GetCharacter());

	FVector Center = MACB->SpawnPos;
	
	float radius = MACB->PatrolRadius;
	float xPos = FMath::RandRange(0.f, radius);
	float yPos = FMath::RandRange(0.f, radius);


	MACB->PatrolPos = FVector(Center.X + xPos, Center.Y + yPos, 0.0f);

	if (cm->pawnSensing)
		cm->pawnSensing->OnSeePawn.AddDynamic(this, &UMPatrolState::PawnSeen);
}

void UMPatrolState::OnTickState()
{
	AMonsterAIControllerBase* MACB = Cast<AMonsterAIControllerBase>(GetController());
	ACharacterMonster* cm = Cast<ACharacterMonster>(MACB->GetCharacter());

	if (MACB->InDestRange(MACB->PatrolPos, 100.0f))
	{
		cm->StateMachineComponent->ChangeState(ECreatureState::Idle);
	}
	else
	{
		MACB->MoveToPosition(MACB->PatrolPos);
	}

}

void UMPatrolState::OnExitState(ECreatureState post)
{
	AMonsterAIControllerBase* MACB = Cast<AMonsterAIControllerBase>(GetController());
	ACharacterMonster* cm = Cast<ACharacterMonster>(MACB->GetCharacter());
	cm->pawnSensing->OnSeePawn.Clear();
}


void UMPatrolState::PawnSeen(APawn* SeenPawn)
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

			// 추적 행동 변경
			cm->StateMachineComponent->ChangeState(ECreatureState::Chase);
		}
	}
}
