// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/BaseState.h"
#include "MReturnState.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UMReturnState : public UBaseState
{
	GENERATED_BODY()
	
public:
	UMReturnState();

	virtual void OnEnterState();
	virtual void OnTickState();
	virtual void OnExitState(ECreatureState post);

};
