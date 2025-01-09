// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Player/DodgeState.h"
#include "PlayerControllerBase.h"
#include "CharacterPlayer.h"
#include "AnimInstanceBase.h"
#include "Stat.h"
#include "GameFramework/CharacterMovementComponent.h"

UDodgeState::UDodgeState()
{
}

void UDodgeState::Init(AController* pc, UAnimMontage* montages)
{
	controller = pc;
	DodgeMontage = montages;
}

bool UDodgeState::OnCheckEnterState()
{
	if (DodgeMontage)
		return true;

	return false;
}

void UDodgeState::OnEnterState()
{
	APlayerControllerBase* APB = GetPlayerControllerBase();
	UAnimInstanceBase* animBase = Cast<UAnimInstanceBase>(APB->GetCharacter()->GetMesh()->GetAnimInstance());
	
	const FRotator Rotation = APB->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	APB->GetCharacter()->SetActorRotation(YawRotation);

	InputValue = APB->PreMoveInputAxisVector;
	if (DodgeMontage)
	{
		FName Name;
		if (InputValue.X == 1 && InputValue.Y == 0) // w (앞)
			Name = "Forward";
		else if (InputValue.X == -1 && InputValue.Y == 0) // s (뒤)
			Name = "Backward";
		else if (InputValue.X == 0 && InputValue.Y == 1) // d (오른쪽)
			Name = "Right";
		else
			Name = "Left";

		animBase->Montage_Play(DodgeMontage, 1.5f);
		animBase->Montage_JumpToSection(Name, DodgeMontage);
	}
}

void UDodgeState::OnTickState()
{
}

void UDodgeState::OnExitState(ECreatureState post)
{
}
