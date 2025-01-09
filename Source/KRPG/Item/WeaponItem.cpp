// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WeaponItem.h"
#include "WeaponItemData.h"

UWeaponItem::UWeaponItem()
{
}

UWeaponItemData* UWeaponItem::GetItemData()
{
	return Cast<UWeaponItemData>(ItemData);
}

void UWeaponItem::SetItemData(UWeaponItemData& data)
{
	Super::SetItemData(data);
}
