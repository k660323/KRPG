// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/WeaponItemData.h"
#include "WeaponItem.h"

UWeaponItemData::UWeaponItemData()
{
}

void UWeaponItemData::SetItemData(FWeaponTableItemData& data)
{
	Super::SetItemData(data);
	PhysicalDamage = data.PhysicalDamage;
	MagicDamage = data.MagicDamage;
}

UItem* UWeaponItemData::CreateItem()
{
	UWeaponItem* item = NewObject<UWeaponItem>();
	item->SetItemData(*this);
	return item;
}
