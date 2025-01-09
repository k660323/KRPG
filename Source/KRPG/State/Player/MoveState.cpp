// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveState.h"
#include "../ControllerEx/Player/PlayerControllerBase.h"

UMoveState::UMoveState()
{
}

void UMoveState::OnEnterState()
{
}

void UMoveState::OnTickState()
{
	APlayerControllerBase* APB = GetPlayerControllerBase();
	const FRotator Rotation = APB->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);


	if (APawn* ControlledPawn = APB->GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, APB->MoveInputAxisVector.X);
		ControlledPawn->AddMovementInput(RightDirection, APB->MoveInputAxisVector.Y);
	}
}

void UMoveState::OnExitState(ECreatureState post)
{
}
