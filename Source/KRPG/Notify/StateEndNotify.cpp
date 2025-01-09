// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/StateEndNotify.h"
#include "CharacterBase.h"
#include "StateMachineComponent.h"
#include "BaseState.h"
#include "IdleState.h"
#include "MIdleState.h"

void UStateEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (ACharacterBase* acb = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		acb->StateMachineComponent->ChangeState(ECreatureState::Idle);
	}
}

void UStateEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (ACharacterBase* acb = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		acb->StateMachineComponent->ChangeState(ECreatureState::Idle);
	}
}
