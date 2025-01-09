// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"
#include "ItemData.h"

UItem::UItem()
{

}

UItemData* UItem::GetItemData()
{
    return ItemData;
}

void UItem::SetItemData(UItemData& data)
{
	ItemData = &data;
}
