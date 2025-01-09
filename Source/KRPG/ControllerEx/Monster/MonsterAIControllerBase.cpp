// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIControllerBase.h"
#include "CharacterBase.h"

bool AMonsterAIControllerBase::InTargetRange(AActor* InTarget, double Radius)
{
	if (InTarget == nullptr)
		return false;

	double DistanceToTarget = (InTarget->GetActorLocation() - GetCharacter()->GetActorLocation()).Size();
    return DistanceToTarget <= Radius;
}

void AMonsterAIControllerBase::MoveToTarget(AActor* InTarget)
{
	if (InTarget)
	{
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(InTarget);
		MoveRequest.SetAcceptanceRadius(15.f);

		FNavPathSharedPtr NavPath;
		MoveTo(MoveRequest, &NavPath);
	}
}

bool AMonsterAIControllerBase::OutDestDistance(FVector dest, double Radius)
{
	double DistanceToDest = (dest - GetCharacter()->GetActorLocation()).Size();
	return DistanceToDest >= Radius;
}

bool AMonsterAIControllerBase::InDestRange(FVector dest, double Radius)
{
	double DistanceToTarget = (dest - GetCharacter()->GetActorLocation()).Size();
	return DistanceToTarget <= Radius;
}

void AMonsterAIControllerBase::MoveToPosition(FVector dest)
{
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(dest);
	MoveRequest.SetAcceptanceRadius(15.f);

	FNavPathSharedPtr NavPath;
	MoveTo(MoveRequest, &NavPath);
}
