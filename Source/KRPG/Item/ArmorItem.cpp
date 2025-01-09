// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ArmorItem.h"
#include "ArmorItemData.h"

UArmorItem::UArmorItem()
{
}

UArmorItemData* UArmorItem::GetItemData()
{
	return Cast<UArmorItemData>(ItemData);
}

void UArmorItem::SetItemData(UArmorItemData& data)
{
	Super::SetItemData(data);
}
