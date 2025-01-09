// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDataTable.h"
#include "PortionItem.h"


FItemTableData::FItemTableData() : ItemGrade(EItemGrade::None), ItemType(EItemType::Etc)
{
}

FCountableItemTableData::FCountableItemTableData() :  MaxAmount(99)
{
	ItemType = EItemType::Countable;
}

FPortionItemTableData::FPortionItemTableData() : Value(0), PortionSubClass(UPortionItem::StaticClass())
{
	ItemType = EItemType::Portion;
}

FEquipmentItemTableData::FEquipmentItemTableData() : EquipType(EEquipType::None), RequireLevel(1), InfinityDurability(true), MaxDurability(100)
{
	ItemType = EItemType::None;
}

FWeaponTableItemData::FWeaponTableItemData() : PhysicalDamage(1)
{
	ItemType = EItemType::Weapon;
}

FArmorTableItemData::FArmorTableItemData() : PhysicalDefence(1)
{
	ItemType = EItemType::Armor;
}
