// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemData.h"
#include "EquipmentItemData.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UEquipmentItemData : public UItemData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		EEquipType EquipType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		int32 RequireLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		bool InfinityDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		int32 MaxDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		int32 STR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		int32 INT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		int32 DEX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		int32 LUK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		float AtkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		float Critical;
public:
	UEquipmentItemData();

	void SetItemData(FEquipmentItemTableData& data);

	virtual UItem* CreateItem() override;
};