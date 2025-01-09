// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/BaseState.h"
#include "RollState.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API URollState : public UBaseState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RollAnim", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* RollMontages;

public:
	URollState();

	virtual void Init(AController* pc, UAnimMontage* montages);

	virtual void OnEnterState() override;
	virtual void OnTickState() override;
	virtual void OnExitState(ECreatureState post) override;
};
