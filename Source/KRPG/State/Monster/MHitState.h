// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/BaseState.h"
#include "MHitState.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UMHitState : public UBaseState
{
	GENERATED_BODY()

private:
	UAnimMontage* montage;

public:
	UMHitState();

	virtual void Init(AController* pc, UAnimMontage* montages);

	virtual void OnEnterState();
	virtual void OnTickState();
	virtual void OnExitState(ECreatureState post);
};
