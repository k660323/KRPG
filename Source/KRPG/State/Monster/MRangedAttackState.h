// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/BaseState.h"
#include "MRangedAttackState.generated.h"


class AController;
class UAnimMontage;
class AProjectile;
/**
 * 
 */
UCLASS()
class KRPG_API UMRangedAttackState : public UBaseState
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AProjectile> ProjectileClass;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackAnim", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 AttackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		bool IsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		bool SaveAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		bool bWeaponActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		FVector attackSize;

	UPROPERTY()
		TSet<AActor*> WeaponAttackTargets;

public:
	UMRangedAttackState();

	// 根鸥林 积己磊俊辑 持绢林扁
	virtual void Init(AController* pc, FVector atkSize, TSubclassOf<UObject> projectileClass) override;
	// 根鸥林 持绢林扁
	virtual void Init(AController* pc, FVector atkSize, UAnimMontage* montage, TSubclassOf<UObject> projectileClass) override;

	virtual void OnEnterState() override;
	virtual void OnTickState() override;
	virtual void OnExitState(ECreatureState post) override;

	UFUNCTION()
		virtual void OnRangedAttack();
	
};
