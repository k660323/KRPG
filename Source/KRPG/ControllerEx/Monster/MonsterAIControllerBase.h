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

	// 추적을 시작한 위치
	UPROPERTY(BlueprintReadWrite, Category = "AI Navigation")
		FVector ChaseStartPos;
	
	// 쫒아갈수있는 거리
	UPROPERTY(BlueprintReadWrite, Category = "AI Navigation")
		float MaxChaseDistance;

	// 공격 상태 넘어가기전
	UPROPERTY(BlueprintReadWrite, Category = "AI Navigation")
		float atkRadius;

	UPROPERTY(BlueprintReadWrite, Category = "Patrol")
		FVector PatrolPos;

	UPROPERTY(BlueprintReadWrite, Category = "Patrol")
		float PatrolRadius;

	//////////////////////////////////////////////////////////////////
	// 추적 대상
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
