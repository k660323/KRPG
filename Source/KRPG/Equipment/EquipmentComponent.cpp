// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/EquipmentComponent.h"
#include "EquipmentItem.h"
#include "EquipmentItemData.h"
#include "InventoryComponent.h"
#include "CharacterPlayer.h"
#include "PlayerControllerBase.h"
#include "KRPGHUD.h"
#include "EquipmentWindowWidget.h"
#include "Stat.h"
#include "WeaponItemData.h"
#include "ArmorItemData.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	InventoryComponent = GetOwner()->FindComponentByClass<UInventoryComponent>();

	if (ACharacterPlayer* cp = Cast<ACharacterPlayer>(GetOwner()))
	{
		if (APlayerControllerBase* pcb = Cast<APlayerControllerBase>(cp->GetController()))
		{
			if (AKRPGHUD* KRPGHUD = Cast<AKRPGHUD>(pcb->GetHUD()))
			{
				EquipmentWindowWidget = Cast<UEquipmentWindowWidget>(KRPGHUD->EquipmentWindowWidget);
				InventoryComponent = GetOwner()->FindComponentByClass<UInventoryComponent>();

				ENetRole role = GetOwner()->GetLocalRole();
				if (role == ENetRole::ROLE_Authority || role == ENetRole::ROLE_AutonomousProxy)
				{
					EquipmentWindowWidget->SetEquipmentWindowReference(this);
				}

			}
		}
	}
}

bool UEquipmentComponent::EquipEquipment(int32 index, UEquipmentItem* equipItem)
{
	if (equipItem == nullptr)
		return false;

	UEquipmentItemData* data = equipItem->GetItemData();
	if (data == nullptr)
		return false;

	UEquipmentItem** equipedItem = equipItems.Find(data->EquipType);
	if (equipedItem == nullptr)
	{
		// 바로 장착
		equipItems.Add({data->EquipType, equipItem });
		// 능력치 조정
		UpdateStat(equipItem, true);
		// 인벤토리 제거
		InventoryComponent->Remove(index);
	}
	else
	{
		// 능력치 조정(능력치 깜)
		UpdateStat(*equipedItem, false);
		// 능력치 조정(능력치 업)
		UpdateStat(equipItem, true);

		// 탈착된 아이템을 인벤토리에 덮어쓰기
		InventoryComponent->OverWriteItem(*equipedItem, index);

		//equipItems.Remove(data->EquipType);
		// 새로 장착될 아이템을 장비창에 덮어쓰기
		equipItems.Add({ data->EquipType ,equipItem });
	}

	// Equipment UI 업데이트
	EquipmentWindowWidget->SetItemIconEvt(data->EquipType, data->IconTexture);

	return true;
}

bool UEquipmentComponent::Unequip(UEquipmentItem* UnequipItem)
{
	if (UnequipItem == nullptr)
		return false;

	UEquipmentItemData* data = UnequipItem->GetItemData();
	if (data == nullptr)
		return false;

	UEquipmentItem** equipedItem = equipItems.Find(data->EquipType);
	if (equipedItem == nullptr)
		return false;

	// 인벤토리 여유가 있는지 확인
	if (InventoryComponent->FindEmptySlotIndex() > -1)
	{
		// 능력치 조정(능력치 깜)
		UpdateStat(*equipedItem, false);

		// 장비창에서 제거
		equipItems.Remove(data->EquipType);

		// UI Slot 이미지 제거
		equipItems.Remove(data->EquipType);

		// 인벤토리 아이템 추가
		InventoryComponent->AddItem(UnequipItem);

		UpdateUISlot(data->EquipType);
		return true;
	}
	else
	{
		return false;
	}
}

void UEquipmentComponent::UpdateUISlot(EEquipType type)
{
	UEquipmentItem** ei = equipItems.Find(type);
	if (ei == nullptr)
	{
		EquipmentWindowWidget->SetItemIconEvt(type, nullptr);
	}
	else
	{
		EquipmentWindowWidget->SetItemIconEvt(type, (*ei)->GetItemData()->IconTexture);
	}
}

void UEquipmentComponent::UpdateStat(UEquipmentItem* equipItem, bool IsEquip)
{
	ACharacterPlayer* cp = Cast<ACharacterPlayer>(GetOwner());
	if (cp == nullptr)
		return;
	UStat* stat = cp->stat;
	if (stat == nullptr)
		return;

	if (IsEquip)
	{
		UEquipmentItemData* data = equipItem->GetItemData();
		stat->SetAdditiveSTR(data->STR);
		stat->SetAdditiveINT(data->INT);
		stat->SetAdditiveDEX(data->DEX);
		stat->SetAdditiveLUK(data->LUK);
		stat->SetAdditiveAtkSpeed(data->AtkSpeed);
		stat->SetAdditiveCritical(data->Critical);

		if (UWeaponItemData* weaponData = Cast<UWeaponItemData>(data))
		{
			stat->SetAdditivePhysicalAttack(weaponData->PhysicalDamage);
			stat->SetAdditiveMagicAttack(weaponData->MagicDamage);
		}
		else if (UArmorItemData* armorData = Cast<UArmorItemData>(data))
		{
			stat->SetAdditivePhysicalDefence(armorData->PhysicalDefence);
			stat->SetAdditiveMagicDefence(armorData->MagicDefence);
			stat->SetAdditiveHpRecovery(armorData->HpRecovery);
			stat->SetAdditiveMpRecovery(armorData->MpRecovery);
			stat->SetAdditiveJumpCount(armorData->JumpCount);
			stat->SetAdditiveJumpZVelocity(armorData->JumpZVelocity);
			stat->SetAdditiveAirControl(armorData->AirControl);
			stat->SetAdditiveMaxWalkSpeed(armorData->MaxWalkSpeed);
			stat->SetAdditiveMinAnalogWalkSpeed(armorData->MinAnalogWalkSpeed);
			stat->SetAdditiveMaxHp(armorData->MaxHp);
			stat->SetAdditiveMaxMp(armorData->MaxMp);
		}
	}
	else
	{
		UEquipmentItemData* data = equipItem->GetItemData();
		stat->SetAdditiveSTR(-data->STR);
		stat->SetAdditiveINT(-data->INT);
		stat->SetAdditiveDEX(-data->DEX);
		stat->SetAdditiveLUK(-data->LUK);
		stat->SetAdditiveAtkSpeed(-data->AtkSpeed);
		stat->SetAdditiveCritical(-data->Critical);

		if (UWeaponItemData* weaponData = Cast<UWeaponItemData>(data))
		{
			stat->SetAdditivePhysicalAttack(-weaponData->PhysicalDamage);
			stat->SetAdditiveMagicAttack(-weaponData->MagicDamage);
		}
		else if (UArmorItemData* armorData = Cast<UArmorItemData>(data))
		{
			stat->SetAdditivePhysicalDefence(-armorData->PhysicalDefence);
			stat->SetAdditiveMagicDefence(-armorData->MagicDefence);
			stat->SetAdditiveHpRecovery(-armorData->HpRecovery);
			stat->SetAdditiveMpRecovery(-armorData->MpRecovery);
			stat->SetAdditiveJumpCount(-armorData->JumpCount);
			stat->SetAdditiveJumpZVelocity(-armorData->JumpZVelocity);
			stat->SetAdditiveAirControl(-armorData->AirControl);
			stat->SetAdditiveMaxWalkSpeed(-armorData->MaxWalkSpeed);
			stat->SetAdditiveMinAnalogWalkSpeed(-armorData->MinAnalogWalkSpeed);
			stat->SetAdditiveMaxHp(-armorData->MaxHp);
			stat->SetAdditiveMaxMp(-armorData->MaxMp);
			stat->SetCurHp(stat->GetCurHp());
			stat->SetCurMp(stat->GetCurMp());
		}
	}
}
