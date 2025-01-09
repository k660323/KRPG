// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include <Define.h>
#include "EquipmentItem.generated.h"

class UEquipmentItemData;
/**
 * 
 */
UCLASS()
class KRPG_API UEquipmentItem : public UItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		bool InfinityDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		int32 Durability;

public:
	UEquipmentItem();

	UEquipmentItemData* GetItemData();

	void SetItemData(UEquipmentItemData& data);


};
