// Fill out your copyright notice in the Description page of Project Settings.


#include "State/BaseState.h"
#include "PlayerControllerBase.h"
#include "MonsterAIControllerBase.h"
#include "GameFramework/Controller.h"

UBaseState::UBaseState()
{
	
}

void UBaseState::Init(AController* pc)
{
	controller = pc;
}

AController* UBaseState::GetController()
{
	return controller;
}

APlayerControllerBase* UBaseState::GetPlayerControllerBase()
{
	return CastChecked<APlayerControllerBase>(controller);
}

AMonsterAIControllerBase* UBaseState::GetAIController()
{
	return CastChecked<AMonsterAIControllerBase>(controller);
}
