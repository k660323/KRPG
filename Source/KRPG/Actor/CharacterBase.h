// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <iostream>
#include "Combatable.h"
#include "CharacterBase.generated.h"

class UStat;
class UStaticMeshComponent;
class UStateMachineComponent;
class UPawnSensingComponent;

UCLASS(config = Game, BlueprintType, meta = (ShortTooltip = "BaseCreatureClass"))
class KRPG_API ACharacterBase : public ACharacter, public ICombatable
{
	GENERATED_BODY()

protected:
	// TEMP 장비창 추가 되면 이동예정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		TObjectPtr<UStaticMeshComponent> Weapon;

public:
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UPawnSensingComponent> pawnSensing;

	// 해당 플레이어 클래스에서 컴포넌트 할당
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStateMachineComponent> StateMachineComponent;
	// 해당 플레이어 클래스에서 컴포넌트 할당
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		TObjectPtr<UStat> stat;

	// TEMP 장비창 추가 되면 이동예정
	UPROPERTY(EditAnywhere, Category = "Combat")
		FName WeaponTipSocketName;
public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Init();
	virtual void InitPawnSensing();
	virtual void AllocatedMachine();
	virtual FVector GetCombatSocketLocation() override;
public:
	UFUNCTION(BlueprintCallable)
	void BindCharacterMovement(float Value);
	UFUNCTION(BlueprintCallable)
	void BindJumpZVelocity(float Value);
	UFUNCTION(BlueprintCallable)
	void BindAirControl(float Value);
	UFUNCTION(BlueprintCallable)
	void BindMaxWalkSpeed(float Value) ;
	UFUNCTION(BlueprintCallable)
	void BindMinAnalogWalkSpeed(float Value);
	UFUNCTION(BlueprintCallable)
	void BindJumpMaxCount(int32 Value);
};
