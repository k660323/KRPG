// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Monster/MDieState.h"
#include "CharacterBase.h"
#include "MonsterAIControllerBase.h"
#include "AnimInstanceBase.h"

UMDieState::UMDieState() : DestroyTime(5.f)
{
}

void UMDieState::Init(AController* pc, UAnimMontage* montages)
{
	controller = pc;
	DieMontages = montages;
}

void UMDieState::OnEnterState()
{
	if (DieMontages)
	{
		AMonsterAIControllerBase* MACB = GetAIController();
		UAnimInstanceBase* animBase = Cast<UAnimInstanceBase>(MACB->GetCharacter()->GetMesh()->GetAnimInstance());

		int32 dieIndex = FMath::RandRange(0, DieMontages->GetNumSections());
		animBase->Montage_Play(DieMontages);
		animBase->Montage_JumpToSection(FName(FString::FromInt(dieIndex)), DieMontages);
	}

	FTimerHandle timer;
	controller->GetWorld()->GetTimerManager().SetTimer(timer, FTimerDelegate::CreateLambda([this]() {

		AMonsterAIControllerBase* MACB = GetAIController();
		TArray<AActor*> AttachedActors;
		MACB->GetCharacter()->GetAttachedActors(AttachedActors);
		for (auto* Attached : AttachedActors)
			Attached->Destroy();
		MACB->GetCharacter()->LifeSpanExpired();
		}), DestroyTime, false);
}

void UMDieState::OnTickState()
{
}

void UMDieState::OnExitState(ECreatureState post)
{

}
