// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpState.h"
#include "../ControllerEx/Player/PlayerControllerBase.h"
#include "CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StateMachineComponent.h"

UJumpState::UJumpState()
{
}

void UJumpState::OnEnterState()
{
	APlayerControllerBase* APB = GetPlayerControllerBase();
	APB->GetCharacter()->Jump();
}

void UJumpState::OnTickState()
{
	APlayerControllerBase* APB = GetPlayerControllerBase();

	bool isFalling = APB->GetCharacter()->GetCharacterMovement()->IsFalling();
	if (!isFalling)
	{
		if (ACharacterBase* ACP = Cast<ACharacterBase>(APB->GetCharacter()))
		{
			if (TObjectPtr<UJumpState> atk = CastChecked<UJumpState>(ACP->StateMachineComponent->GetState(ECreatureState::Jump)))
			{
				ACP->StateMachineComponent->ChangeState(ECreatureState::Idle);
			}
		}
	}
}

void UJumpState::OnExitState(ECreatureState post)
{
	
}
