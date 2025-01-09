// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyState/AttackNotifyState.h"
#include "CharacterBase.h"
#include "StateMachineComponent.h"
#include "BaseState.h"
#include "AttackState.h"
#include "MAttackState.h"
#include "SkillState.h"

void UAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (ACharacterBase* acb = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		UBaseState* curstate = acb->StateMachineComponent.Get()->GetCurrentState();
		if (UAttackState* atkState = Cast<UAttackState>(curstate))
		{
			atkState->bWeaponActive = true;
		}
		else if (UMAttackState* MatkState = Cast<UMAttackState>(curstate))
		{
			MatkState->bWeaponActive = true;
		}
		else if (USkillState* skillatkState = Cast<USkillState>(curstate))
		{
			skillatkState->bWeaponActive = true;
		}
	}
}

void UAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ACharacterBase* acb = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		UBaseState* curstate = acb->StateMachineComponent.Get()->GetCurrentState();

		if (UAttackState* atkState = Cast<UAttackState>(curstate))
		{
			atkState->bWeaponActive = false;
		}	
		else if (UMAttackState* MatkState = Cast<UMAttackState>(curstate))
		{
			MatkState->bWeaponActive = false;
		}	
		else if (USkillState* skillatkState = Cast<USkillState>(curstate))
		{
			skillatkState->bWeaponActive = false;
		}
	}
}
