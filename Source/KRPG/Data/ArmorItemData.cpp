// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ArmorItemData.h"
#include "ArmorItem.h"

UArmorItemData::UArmorItemData()
{
}

void UArmorItemData::SetItemData(FArmorTableItemData& data)
{
	Super::SetItemData(data);
	PhysicalDefence = data.PhysicalDefence;
	MagicDefence = data.MagicDefence;
	HpRecovery = data.HpRecovery;
	MpRecovery = data.MpRecovery;
	JumpCount = data.JumpCount;
	JumpZVelocity = data.JumpZVelocity;
	AirControl = data.AirControl;
	MaxWalkSpeed = data.MaxWalkSpeed;
	MinAnalogWalkSpeed = data.MinAnalogWalkSpeed;
	MaxHp = data.MaxHp;
	MaxMp = data.MaxMp;
}

UItem* UArmorItemData::CreateItem()
{
	UArmorItem* item = NewObject<UArmorItem>();
	item->SetItemData(*this);
	return item;
}
