// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/CountableItem.h"
#include "CountableItemData.h"

UCountableItem* UCountableItem::Clone(int _amount)
{
	UCountableItem* countable = NewObject<UCountableItem>();
	countable->SetItemData(*GetItemData(), _amount);
	return countable;
}

UCountableItem::UCountableItem()
{
}

UCountableItemData* UCountableItem::GetItemData()
{
	return Cast<UCountableItemData>(ItemData);
}

void UCountableItem::SetItemData(UCountableItemData& data, int32 _amount)
{
	Super::SetItemData(data);
	SetAmount(_amount);
}

int32 UCountableItem::MaxAmount()
{
	return GetItemData()->MaxAmount;
}

bool UCountableItem::IsMax()
{
	return Amount >= MaxAmount();
}

bool UCountableItem::IsEmpty()
{
	return Amount <= 0;
}

void UCountableItem::SetAmount(int32 _amount)
{
	Amount = FMath::Clamp(_amount, 0, MaxAmount());
}

int32 UCountableItem::AddAmountAndGetExcess(int32 _amount)
{
	int nextAmount = Amount + _amount;
	SetAmount(nextAmount);

	return (nextAmount > MaxAmount()) ? (nextAmount - MaxAmount()) : 0;
}

UCountableItem* UCountableItem::SeperateAndClone(int _amount)
{
	// 수량이 한개 이하일 경우, 복제 불가
	if (Amount <= 1)
		return nullptr;

	if (_amount > Amount - 1)
		_amount = Amount - 1;

	Amount -= _amount;


	return Clone(_amount);
}
