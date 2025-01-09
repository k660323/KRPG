// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAIControllerBase.generated.h"

class ACharacterBase;
/**
 * 
 */
UCLASS()
class KRPG_API AMonsterAIControllerBase : public AAIController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "AI Navigation")
		FVector SpawnPos;

	// ������ ������ ��ġ
	UPROPERTY(BlueprintReadWrite, Category = "AI Navigation")
		FVector ChaseStartPos;
	
	// �i�ư����ִ� �Ÿ�
	UPROPERTY(BlueprintReadWrite, Category = "AI Navigation")
		float MaxChaseDistance;

	// ���� ���� �Ѿ����
	UPROPERTY(BlueprintReadWrite, Category = "AI Navigation")
		float atkRadius;

	UPROPERTY(BlueprintReadWrite, Category = "Patrol")
		FVector PatrolPos;

	UPROPERTY(BlueprintReadWrite, Category = "Patrol")
		float PatrolRadius;

	//////////////////////////////////////////////////////////////////
	// ���� ���
	UPROPERTY(BlueprintReadWrite, Category = "AI Navigation")
		ACharacterBase* CombatTarget;

public:
	UFUNCTION()
		virtual bool InTargetRange(AActor* InTarget, double Radius);

	UFUNCTION()
		virtual void MoveToTarget(AActor* InTarget);

	UFUNCTION()
		virtual bool OutDestDistance(FVector dest, double Radius);

	UFUNCTION()
		virtual bool InDestRange(FVector dest, double Radius);

	UFUNCTION()
		virtual void MoveToPosition(FVector dest);
};
