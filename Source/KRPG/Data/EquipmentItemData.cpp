// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/EquipmentItemData.h"
#include "EquipmentItem.h"
UEquipmentItemData::UEquipmentItemData()
{
}

void UEquipmentItemData::SetItemData(FEquipmentItemTableData& data)
{
	Super::SetItemData(data);
	EquipType = data.EquipType;
	RequireLevel = data.RequireLevel;
	InfinityDurability = data.InfinityDurability;
	MaxDurability = data.MaxDurability;
	STR = data.STR;
	INT = data.INT;
	DEX = data.DEX;
	LUK = data.LUK;
	AtkSpeed = data.AtkSpeed;
	Critical = data.Critical;
}

UItem* UEquipmentItemData::CreateItem()
{
	UEquipmentItem* item = NewObject<UEquipmentItem>();
	item->SetItemData(*this);
	return item;
}
