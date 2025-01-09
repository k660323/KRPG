// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/StateMachineComponent.h"
#include "../ControllerEx/Player/PlayerControllerBase.h"
#include "BaseState.h"
#include <Define.h>

UStateMachineComponent::UStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	EState = ECreatureState::None;
}


void UStateMachineComponent::InitState(ECreatureState stateName, UBaseState* state)
{
	AddState(stateName, state);
	ChangeState(stateName);
	//currentState = GetState(stateName);
	//currentState.Get()->OnEnterState();
	//EState = stateName;
}

UBaseState* UStateMachineComponent::GetCurrentState()
{
	return currentState;
}

void UStateMachineComponent::AddState(ECreatureState stateName, UBaseState* state)
{
	if (!states.Contains(stateName))
	{
		states.Add({ stateName,state });
	}
}

UBaseState* UStateMachineComponent::GetState(ECreatureState stateName)
{
	if (states.Contains(stateName))
	{
		return states[stateName];
	}

	return nullptr;
}

void UStateMachineComponent::DeleteState(ECreatureState removeStateName)
{
	if (states.Contains(removeStateName))
	{
		states.Remove(removeStateName);
	}
}

void UStateMachineComponent::ChangeState(ECreatureState nextStateName)
{
	if (states.Contains(nextStateName))
	{
		if (states[nextStateName]->OnCheckEnterState())
		{
			if (currentState != nullptr)
				currentState.Get()->OnExitState(nextStateName);

			currentState = states[nextStateName];
			EState = nextStateName;

			currentState.Get()->OnEnterState();
		}
	}
}

void UStateMachineComponent::TickState()
{
	if (currentState == nullptr)
		return;

	currentState.Get()->OnTickState();
}

void UStateMachineComponent::AddSkillState(FGameplayTag keyTagName, UBaseState* state)
{
	if (!skillStates.Contains(keyTagName))
	{
		skillStates.Add({ keyTagName,state });
	}
}

UBaseState* UStateMachineComponent::GetSkillState(FGameplayTag keyTagName)
{
	if (skillStates.Contains(keyTagName))
	{
		return skillStates[keyTagName];
	}

	return nullptr;
}

void UStateMachineComponent::DeleteSkillState(FGameplayTag removeStateName)
{
	if (skillStates.Contains(removeStateName))
	{
		skillStates.Remove(removeStateName);
	}
}

void UStateMachineComponent::ChangeSkillState(FGameplayTag nextStateName)
{
	if (skillStates.Contains(nextStateName))
	{
		if (skillStates[nextStateName]->OnCheckEnterState())
		{
			if (currentState != nullptr)
				currentState.Get()->OnExitState(ECreatureState::Skill);

			currentState = skillStates[nextStateName];
			EState = ECreatureState::Skill;

			currentState.Get()->OnEnterState();
		}
	}
}

// Called when the game starts
void UStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
