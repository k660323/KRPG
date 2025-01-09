// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/EquipmentItemData.h"
#include "ArmorItemData.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UArmorItemData : public UEquipmentItemData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorItem")
		int32 PhysicalDefence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int32 MagicDefence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		float HpRecovery;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		float MpRecovery;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int32 JumpCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		float JumpZVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		float AirControl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		float MaxWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		float MinAnalogWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int32 MaxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int32 MaxMp;
public:
	UArmorItemData();

	void SetItemData(FArmorTableItemData& data);

	virtual UItem* CreateItem() override;
};
