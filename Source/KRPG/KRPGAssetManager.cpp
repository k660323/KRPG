// Fill out your copyright notice in the Description page of Project Settings.


#include "KRPGAssetManager.h"
#include "KRPGGameplayTags.h"
#include "StatDataTable.h"
#include "ItemDataTable.h"
#include "ItemData.h"
#include "WeaponItemData.h"
#include "ArmorItemData.h"
#include "PortionItemData.h"
#include <Define.h>

UKRPGAssetManager& UKRPGAssetManager::Get()
{
	check(GEngine);

	UKRPGAssetManager* KRPGAssetManager = Cast<UKRPGAssetManager>(GEngine->AssetManager);
	
	return *KRPGAssetManager;
}

FStatData* UKRPGAssetManager::GetPlayerStatDataTable(ECreaturePlayer type, int32 level)
{
	TObjectPtr<UDataTable> table = PlayerStatTables.Find(ECreaturePlayer::Countness)->Get();

	return table.Get()->FindRow<FStatData>(*FString::FromInt(level), TEXT(""));
}

FStatData* UKRPGAssetManager::GetMonsterStatDataTable(ECreatureMonster type)
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECreatureMonster"), true);
	if (!enumPtr)
		return nullptr;

	return MonsterStatTable.Get()->FindRow<FStatData>(*enumPtr->GetNameStringByIndex((int32)type), TEXT(""));;
}

UItemData* UKRPGAssetManager::GetNewItemData(EItemType type, int32 itemIndex)
{
	TObjectPtr<UDataTable> loadTable = ItemTables[type].Get();

	if (type == EItemType::Weapon)
	{
		FWeaponTableItemData* weaponData = loadTable.Get()->FindRow<FWeaponTableItemData>(*FString::FromInt(itemIndex), TEXT(""));
		TObjectPtr<UWeaponItemData> WeaponItemData = NewObject<UWeaponItemData>();
		WeaponItemData->SetItemData(*weaponData);
		return WeaponItemData;
	}
	else if (type == EItemType::Armor)
	{
		FArmorTableItemData* armorData = loadTable.Get()->FindRow<FArmorTableItemData>(*FString::FromInt(itemIndex), TEXT(""));
		TObjectPtr<UArmorItemData> ArmorItemData = NewObject<UArmorItemData>();
		ArmorItemData->SetItemData(*armorData);
		return ArmorItemData;
	}
	else if (type == EItemType::Portion)
	{
		FPortionItemTableData* portionData = loadTable.Get()->FindRow<FPortionItemTableData>(*FString::FromInt(itemIndex), TEXT(""));
		TObjectPtr<UPortionItemData> PortionItemData = NewObject<UPortionItemData>();
		PortionItemData->SetItemData(*portionData);

		return PortionItemData;
	}

	return nullptr;
}

void UKRPGAssetManager::InitStatData()
{
	UDataTable* data = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/Assets/Data/DT_CountessStat.DT_CountessStat'"));
	if (data)
		PlayerStatTables.Add(ECreaturePlayer::Countness, data);

	data = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/Assets/Data/DT_MonsterStat.DT_MonsterStat'"));
	if (data)
		MonsterStatTable = data;
}

void UKRPGAssetManager::InitItemData()
{
	UDataTable* dataTable = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/Assets/Data/DT_WeaponItem.DT_WeaponItem'"));
	if (dataTable)
		ItemTables.Add(EItemType::Weapon, dataTable);

	dataTable = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/Assets/Data/DT_ArmorItem.DT_ArmorItem'"));
	if (dataTable)
		ItemTables.Add(EItemType::Armor, dataTable);

	dataTable = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/Assets/Data/DT_PortionItem.DT_PortionItem'"));
	if (dataTable)
		ItemTables.Add(EItemType::Portion, dataTable);
}

void UKRPGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FKRPGGameplayTags::InitializeNativeGameplayTags();
	InitStatData();
	InitItemData();
}
