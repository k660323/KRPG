// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/MpPortionItem.h"
#include "PortionItemData.h"
#include "KGameInstance.h"
#include "CharacterPlayer.h"
#include "Stat.h"

UCountableItem* UMpPortionItem::Clone(int _amount)
{
	UMpPortionItem* portion = NewObject<UMpPortionItem>();
	portion->SetItemData(*GetItemData(), _amount);
	return portion;
}

UMpPortionItem::UMpPortionItem()
{
}

bool UMpPortionItem::Use()
{
	if (GWorld == nullptr)
		return false;

	if (UKGameInstance* KGameInstance = Cast<UKGameInstance>(GWorld->GetGameInstance()))
	{
		if (KGameInstance->MyPlayer == nullptr)
			return false;

		ACharacterPlayer* CharacterPlayer = Cast<ACharacterPlayer>(KGameInstance->MyPlayer);
		UStat* stat = CharacterPlayer->stat;

		if (stat->GetCurMp() >= stat->GetMaxMp() + stat->GetAdditiveMaxMp())
			return false;

		UPortionItemData* data = GetItemData();
		stat->SetCurMp(stat->GetCurMp() + data->Value);

		Amount--;
	}

	return true;
}
