// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/EquipmentItemData.h"
#include "WeaponItemData.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UWeaponItemData : public UEquipmentItemData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponItem")
		int32 PhysicalDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponItem")
		int32 MagicDamage;
public:
	UWeaponItemData();

	void SetItemData(FWeaponTableItemData& data);

	virtual UItem* CreateItem() override;
};
