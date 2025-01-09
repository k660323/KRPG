// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HpPortionItem.h"
#include "PortionItemData.h"
#include "KGameInstance.h"
#include "CharacterPlayer.h"
#include "Stat.h"

UCountableItem* UHpPortionItem::Clone(int _amount)
{
	UHpPortionItem* portion = NewObject<UHpPortionItem>();
	portion->SetItemData(*GetItemData(), _amount);
	return portion;
}

UHpPortionItem::UHpPortionItem()
{
}

bool UHpPortionItem::Use()
{
	if (GWorld == nullptr)
		return false;

	if (UKGameInstance* KGameInstance = Cast<UKGameInstance>(GWorld->GetGameInstance()))
	{
		if (KGameInstance->MyPlayer == nullptr)
			return false;

		ACharacterPlayer* CharacterPlayer = Cast<ACharacterPlayer>(KGameInstance->MyPlayer);
		UStat* stat = CharacterPlayer->stat;

		if (stat->GetCurHp() >= stat->GetMaxHp() + stat->GetAdditiveMaxHp())
			return false;

		UPortionItemData* data = GetItemData();
		stat->SetCurHp(stat->GetCurHp() + data->Value);

		Amount--;
	}
	
	return true;
}
