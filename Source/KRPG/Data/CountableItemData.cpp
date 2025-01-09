// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/CountableItemData.h"
#include "CountableItem.h"

UCountableItemData::UCountableItemData()
{
}

void UCountableItemData::SetItemData(FCountableItemTableData& data)
{
	Super::SetItemData(data);
	MaxAmount = data.MaxAmount;
}

UItem* UCountableItemData::CreateItem()
{
	UCountableItem* item = NewObject<UCountableItem>();
	item->SetItemData(*this);
	return item;
}
