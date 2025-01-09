// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PortionItem.h"
#include "PortionItemData.h"

UCountableItem* UPortionItem::Clone(int _amount)
{
	UPortionItem* portion = NewObject<UPortionItem>();
	portion->SetItemData(*GetItemData(), _amount);
	return portion;
}

UPortionItem::UPortionItem()
{
}

UPortionItemData* UPortionItem::GetItemData()
{
	return Cast<UPortionItemData>(ItemData);
}

void UPortionItem::SetItemData(UPortionItemData& data, int32 _amount)
{
	Super::SetItemData(data, _amount);
}

bool UPortionItem::Use()
{
	// �ӽ� ���� �ϳ� ����
	Amount--;

	return true;
}
