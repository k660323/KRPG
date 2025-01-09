// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StatDataTable.generated.h"

USTRUCT(BlueprintType)
struct FStatData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FStatData() : Level(0), MaxHp(0), MaxMp(0), JumpCount(1), PhysicalAttack(100), MagicAttack(100), PhysicalDefence(0), MagicDefence(0), STR(0), INT(0), DEX(0), LUK(0), StatCount(0), 
		HpRecovery(1.0f), MpRecovery(1.0f), MaxExp(0.0f), AtkSpeed(1.0f), Critical(0.0f), RotationRate(500.f), JumpZVelocity(500.f), AirControl(0.35f), MaxWalkSpeed(500.f), MinAnalogWalkSpeed(20.f)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 MaxMp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 JumpCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 PhysicalAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 MagicAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 PhysicalDefence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 MagicDefence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 STR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 INT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 DEX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 LUK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 StatCount;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float HpRecovery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float MpRecovery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float MaxExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float AtkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float Critical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterMovementStat")
		float RotationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterMovementStat")
		float JumpZVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterMovementStat")
		float AirControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterMovementStat")
		float MaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterMovementStat")
		float MinAnalogWalkSpeed;
};

/**
 * 
 */
UCLASS()
class KRPG_API UStatDataTable : public UDataTable
{
	GENERATED_BODY()
	
public:

};
