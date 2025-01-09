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
		// �ٷ� ����
		equipItems.Add({data->EquipType, equipItem });
		// �ɷ�ġ ����
		UpdateStat(equipItem, true);
		// �κ��丮 ����
		InventoryComponent->Remove(index);
	}
	else
	{
		// �ɷ�ġ ����(�ɷ�ġ ��)
		UpdateStat(*equipedItem, false);
		// �ɷ�ġ ����(�ɷ�ġ ��)
		UpdateStat(equipItem, true);

		// Ż���� �������� �κ��丮�� �����
		InventoryComponent->OverWriteItem(*equipedItem, index);

		//equipItems.Remove(data->EquipType);
		// ���� ������ �������� ���â�� �����
		equipItems.Add({ data->EquipType ,equipItem });
	}

	// Equipment UI ������Ʈ
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

	// �κ��丮 ������ �ִ��� Ȯ��
	if (InventoryComponent->FindEmptySlotIndex() > -1)
	{
		// �ɷ�ġ ����(�ɷ�ġ ��)
		UpdateStat(*equipedItem, false);

		// ���â���� ����
		equipItems.Remove(data->EquipType);

		// UI Slot �̹��� ����
		equipItems.Remove(data->EquipType);

		// �κ��丮 ������ �߰�
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
