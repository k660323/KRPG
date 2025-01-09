// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemData.h"
#include "Item.h"

UItemData::UItemData()
{
}

UItem* UItemData::CreateItem()
{
	UItem* item = NewObject<UItem>();
	item->SetItemData(*this);
	return item;
}

void UItemData::SetItemData(FItemTableData& data)
{
	ItemGrade = data.ItemGrade;
	ItemType = data.ItemType;
	Name = data.Name;
	Tooltip = data.Tooltip;
	IconTexture = data.IconTexture;
	Price = data.Price;
	WorldItemMesh = data.WorldItemMesh;
}
