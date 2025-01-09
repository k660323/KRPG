// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EquipmentItem.h"
#include "EquipmentItemData.h"

UEquipmentItem::UEquipmentItem()
{
}

UEquipmentItemData* UEquipmentItem::GetItemData()
{
	return Cast<UEquipmentItemData>(ItemData);
}

void UEquipmentItem::SetItemData(UEquipmentItemData& data)
{
	Super::SetItemData(data);
	InfinityDurability = data.InfinityDurability;
	Durability = data.MaxDurability;
}