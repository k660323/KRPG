// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/EquipmentItem.h"
#include "ArmorItem.generated.h"

class UArmorItemData;
/**
 * 
 */
UCLASS()
class KRPG_API UArmorItem : public UEquipmentItem
{
	GENERATED_BODY()
public:
	UArmorItem();

	UArmorItemData* GetItemData();

	void SetItemData(UArmorItemData& data);
};
