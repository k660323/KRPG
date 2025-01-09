// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/PortionItemData.h"
#include "PortionItem.h"

UPortionItemData::UPortionItemData()
{
}

void UPortionItemData::SetItemData(FPortionItemTableData& data)
{
	Super::SetItemData(data);
	Value = data.Value;
	PortionSubClass = data.PortionSubClass;
}

UItem* UPortionItemData::CreateItem()
{
	UPortionItem* item = NewObject<UPortionItem>(this, PortionSubClass);
	item->SetItemData(*this);
	return item;
}
