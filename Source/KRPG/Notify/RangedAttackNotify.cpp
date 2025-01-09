// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/RangedAttackNotify.h"
#include "CharacterBase.h"
#include "StateMachineComponent.h"
#include "BaseState.h"
#include "MRangedAttackState.h"

void URangedAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (ACharacterBase* acb = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		UBaseState* curstate = acb->StateMachineComponent.Get()->GetCurrentState();
		if (UMRangedAttackState* atkState = Cast<UMRangedAttackState>(curstate))
		{
			atkState->OnRangedAttack();
		}
	}
}

void URangedAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (ACharacterBase* acb = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		UBaseState* curstate = acb->StateMachineComponent.Get()->GetCurrentState();
		if (UMRangedAttackState* atkState = Cast<UMRangedAttackState>(curstate))
		{
			atkState->OnRangedAttack();
		}
	}
}
