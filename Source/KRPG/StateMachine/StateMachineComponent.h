// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseState.h"
#include "GameplayTagContainer.h"
#include <Define.h>
#include "StateMachineComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRPG_API UStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ECreatureState EState;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<ECreatureState, TObjectPtr<UBaseState>> states;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, TObjectPtr<UBaseState>> skillStates;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBaseState> currentState;
	
public:	
	// Sets default values for this component's properties
	UStateMachineComponent();
	
	UFUNCTION(BluePrintCallable)
	void InitState(ECreatureState stateName, UBaseState* state);

	UBaseState* GetCurrentState();

	UFUNCTION(BluePrintCallable)
	void AddState(ECreatureState stateName, UBaseState* state);

	UFUNCTION(BluePrintCallable)
	UBaseState* GetState(ECreatureState stateName);

	UFUNCTION(BluePrintCallable)
	void DeleteState(ECreatureState removeStateName);

	UFUNCTION(BluePrintCallable)
	void ChangeState(ECreatureState nextStateName);

	UFUNCTION(BluePrintCallable)
	void AddSkillState(FGameplayTag keyTagName, UBaseState* state);
	
	UFUNCTION(BluePrintCallable)
	UBaseState* GetSkillState(FGameplayTag keyTagName);

	UFUNCTION(BluePrintCallable)
	void DeleteSkillState(FGameplayTag removeStateName);

	UFUNCTION(BluePrintCallable)
	void ChangeSkillState(FGameplayTag nextStateName);

	UFUNCTION(BluePrintCallable)
	void TickState();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
