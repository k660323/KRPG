// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/EquipmentItem.h"
#include "WeaponItem.generated.h"

class UWeaponItemData;
/**
 * 
 */
UCLASS()
class KRPG_API UWeaponItem : public UEquipmentItem
{
	GENERATED_BODY()
public:
	UWeaponItem();

	UWeaponItemData* GetItemData();

	void SetItemData(UWeaponItemData& data);
};
