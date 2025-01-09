// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Define.h>
#include "BaseState.generated.h"


class APlayerControllerBase;
class AMonsterAIControllerBase;
class AController;
class UAnimMontage;
class AProjectile;

/**
 * 
 */
UCLASS(config = Game, BlueprintType, meta = (ShortTooltip = "Character State Define"))
class KRPG_API UBaseState : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		TObjectPtr<AController> controller;
public:
	UBaseState();

	void Init(AController* pc);
	virtual void Init(AController* pc, UAnimMontage* montages) {}
	virtual void Init(AController* pc, FVector atkSize) {}
	virtual void Init(AController* pc, FVector atkSize, UAnimMontage* montage) {};
	virtual void Init(AController* pc, FVector atkSize, TSubclassOf<UObject> projectileClass) {};
	virtual void Init(AController * pc, FVector atkSize, UAnimMontage * montage, TSubclassOf<UObject> projectileClass) {};

	UFUNCTION()
	virtual bool OnCheckEnterState() { return true; }
	UFUNCTION()
	virtual void OnEnterState() {}
	UFUNCTION()
	virtual void OnTickState() {}
	UFUNCTION()
	virtual void OnExitState(ECreatureState post) {}

	AController* GetController();
	APlayerControllerBase* GetPlayerControllerBase();
	AMonsterAIControllerBase* GetAIController();
};
