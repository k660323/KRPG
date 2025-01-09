// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/AttackNotify.h"
#include "CharacterBase.h"
#include "StateMachineComponent.h"
#include "BaseState.h"
#include "AttackState.h"
#include "MAttackState.h"
#include "SkillState.h"

void UAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (ACharacterBase* acb = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		UBaseState* curstate = acb->StateMachineComponent.Get()->GetCurrentState();
		if (UAttackState* atkState = Cast<UAttackState>(curstate))
		{
			atkState->OnAttack();
		}
		else if (UMAttackState* MatkState = Cast<UMAttackState>(curstate))
		{
			atkState->OnAttack();
		}
		else if (USkillState* skillatkState = Cast<USkillState>(curstate))
		{
			atkState->OnAttack();
		}
	}
}

void UAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (ACharacterBase* acb = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		UBaseState* curstate = acb->StateMachineComponent.Get()->GetCurrentState();
		if (UAttackState* atkState = Cast<UAttackState>(curstate))
		{
			atkState->OnAttack();
		}
		else if (UMAttackState* MatkState = Cast<UMAttackState>(curstate))
		{
			atkState->OnAttack();
		}
		else if (USkillState* skillatkState = Cast<USkillState>(curstate))
		{
			atkState->OnAttack();
		}
	}
}
