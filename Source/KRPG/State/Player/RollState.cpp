// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Player/RollState.h"
#include "PlayerControllerBase.h"
#include "CharacterBase.h"
#include "AnimInstanceBase.h"
#include "Stat.h"
#include "GameFramework/CharacterMovementComponent.h"

URollState::URollState()
{
}

void URollState::Init(AController* pc, UAnimMontage* montages)
{
	controller = pc;
	RollMontages = montages;
}

void URollState::OnEnterState()
{
	APlayerControllerBase* APB = GetPlayerControllerBase();
	ACharacterBase* ACP = CastChecked<ACharacterBase>(APB->GetCharacter());
	UAnimInstanceBase* animBase = Cast<UAnimInstanceBase>(ACP->GetMesh()->GetAnimInstance());

	//const FRotator Rotation = APB->GetControlRotation();
	//const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//InputValue = APB->PreMoveInputAxisVector;

	//if (RollMontages)
	//{
	//	ACP->PlayAnimMontage(RollMontages, 2.0f);
	//	FName Name;
	//	Name = "RoolFwd";
	//	//if (APB->PreMoveInputAxisVector.Y < 0) // a
	//	//	Name = "RoolLeft";
	//	//else if (APB->PreMoveInputAxisVector.Y < 0) // d
	//	//	Name = "RoolRight";
	//	//else if (APB->PreMoveInputAxisVector.X < 0) // w
	//	//	Name = "RoolFwd";
	//	//else // d
	//	//	Name = "RoolBack";
	//	//animBase->Montage_JumpToSection(Name, RollMontages);
	//}

	ACP->PlayAnimMontage(RollMontages, 2.0f);
	//animBase->Montage_JumpToSection(Name, RollMontages);
}

void URollState::OnTickState()
{

}

void URollState::OnExitState(ECreatureState post)
{

}
