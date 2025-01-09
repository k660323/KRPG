// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"
#include "InventoryWidget.h"
#include "CharacterPlayer.h"
#include "PlayerControllerBase.h"
#include "KRPGHUD.h"
#include "KRPGAssetManager.h"
#include "ItemData.h"
#include "CountableItemData.h"
#include "UseableItem.h"
#include "Item.h"
#include "CountableItem.h"
#include "PortionItem.h"
#include "EquipmentItem.h"
#include "EquipmentComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	items.SetNum(MaxCapacity);
	Capacity = InitalCapacity;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...

	if (ACharacterPlayer* cp = Cast<ACharacterPlayer>(GetOwner()))
	{
		if (APlayerControllerBase* pcb = Cast<APlayerControllerBase>(cp->GetController()))
		{
			if (AKRPGHUD* KRPGHUD = Cast<AKRPGHUD>(pcb->GetHUD()))
			{
				InventoryWidget = Cast<UInventoryWidget>(KRPGHUD->InventoryWidget);
				EquipmentComponent = GetOwner()->FindComponentByClass<UEquipmentComponent>();

				ENetRole role = GetOwner()->GetLocalRole();
				if (role == ENetRole::ROLE_Authority || role == ENetRole::ROLE_AutonomousProxy)
				{
					InventoryWidget->SetInventoryReference(this);
					UpdateAccessibleStatesAll();
				}
					
			}
		}
	}

	TestItemSpawn(EItemType::Weapon, 0);
	TestItemSpawn(EItemType::Weapon, 1);
	TestItemSpawn(EItemType::Armor, 0);
	TestItemSpawn(EItemType::Portion, 0, 10);
	TestItemSpawn(EItemType::Portion, 0, 10);
	TestItemSpawn(EItemType::Portion, 1, 150);
}

bool UInventoryComponent::IsValidIndex(int index)
{
	return index >= 0 && index < Capacity;
}

int UInventoryComponent::FindEmptySlotIndex(int startIndex)
{
	for (int i = startIndex; i < Capacity; i++)
		if (items[i] == nullptr)
			return i;

	return -1;
}

void UInventoryComponent::UpdateAccessibleStatesAll()
{
	InventoryWidget->SetAccessibleSlotRangeAllEvt(Capacity);
}


bool UInventoryComponent::HasItem(int index)
{
	return IsValidIndex(index) && items[index] != nullptr;
}

bool UInventoryComponent::IsCountableItem(int index)
{
	return HasItem(index) && Cast<UCountableItem>(items[index]);
}

int UInventoryComponent::GetCurrentAmount(int index)
{
	if (!IsValidIndex(index))
		return -1;
	if (items[index] == nullptr)
		return 0;

	UCountableItem* ci = Cast<UCountableItem>(items[index]);
	if (ci == nullptr)
		return 1;

	return ci->Amount;
}

UItemData* UInventoryComponent::GetItemData(int index)
{
	if (!IsValidIndex(index))
		return nullptr;
	if (items[index] == nullptr)
		return nullptr;

	return items[index]->GetItemData();
}



FString UInventoryComponent::GetItemName(int index)
{
	if (!IsValidIndex(index))
		return FString();
	if (items[index] == nullptr)
		return FString();

	return 	items[index]->GetItemData()->Name;
}

void UInventoryComponent::UpdateSlot(int index)
{
	if (!IsValidIndex(index))
		return;

	UItem* item = items[index];

	// 아이템이 슬롯에 존재하는 경우
	if (item != nullptr)
	{
		// 아이콘 등록
		InventoryWidget->SetItemIconEvt(index, item->GetItemData()->IconTexture);

		// 셀 수 있는 아이템
		if (UCountableItem* ci = Cast<UCountableItem>(item))
		{
			if (ci->IsEmpty())
			{
				items[index] = nullptr;
				RemoveIcon(index);
				return;
			}
			else
			{
				InventoryWidget->SetItemAmountTextEvt(index, ci->Amount);
			}
		}
		else // 셀수 없는 아이템 경우 수량 텍스트 제거
		{
			InventoryWidget->HideItemAmountTextEvt(index);
		}
	}
	else // 2. 빈 슬롯인 경우 : 아이콘 제거
	{
		RemoveIcon(index);
	}
}

void UInventoryComponent::UpdateArraySlot(TArray<int>& indexs)
{
	int size = indexs.Num();
	for (int i = 0; i < size; i++)
		UpdateSlot(indexs[i]);
}

void UInventoryComponent::RemoveIcon(int index)
{
	InventoryWidget->RemoveSlotEvt(index);
	InventoryWidget->HideItemAmountTextEvt(index); // 수량 텍스트 숨기기
}

void UInventoryComponent::Swap(int indexA, int indexB)
{
	if (!IsValidIndex(indexA))
		return;
	if (!IsValidIndex(indexB))
		return;

	UItem* itemA = items[indexA];
	UItem* itemB = items[indexB];
	
	if (itemA == nullptr && itemB == nullptr)
		return;


	UCountableItem* ciA = Cast<UCountableItem>(itemA);
	UCountableItem* ciB = Cast<UCountableItem>(itemB);

	// 1. 셀 수 있는 아이템이고, 동일한 아이템일 경우 indexA->indexB로 개수 합치기
	//ciA->GetCountabletItemData() == ciB->GetCountabletItemData()

	if (ciA != nullptr && ciB != nullptr &&
		ciA->GetItemData()->ItemGrade == ciB->GetItemData()->ItemGrade &&
		ciA->GetItemData()->ItemType == ciB->GetItemData()->ItemType &&
		ciA->GetItemData()->Name == ciB->GetItemData()->Name &&
		ciA->GetItemData()->IconTexture == ciB->GetItemData()->IconTexture)
	{		
		int maxAmount = ciB->MaxAmount();
		int sum = ciA->Amount + ciB->Amount;

		if (sum <= maxAmount)
		{
			ciA->SetAmount(0);
			ciB->SetAmount(sum);
		}
		else
		{
			ciA->SetAmount(sum - maxAmount);
			ciB->SetAmount(maxAmount);
		}	
	}
	else // 2. 일반적인 경우 : 슬롯 교체
	{
		items[indexA] = itemB;
		items[indexB] = itemA;
	}

	// 두 슬롯 UI에 정보 갱신
	TArray<int> indexArr;
	indexArr.Add(indexA);
	indexArr.Add(indexB);
	UpdateArraySlot(indexArr);
}

void UInventoryComponent::OverWriteItem(UItem* item, int index)
{
	if (!IsValidIndex(index))
		return;

	items[index] = item;
	UpdateSlot(index);
}

int32 UInventoryComponent::AddItem(UItem* item)
{
	int32 index = 0;
	int amount = 1;

	if (UCountableItem* ci = Cast<UCountableItem>(item))
	{
		bool findNextCountable = true;
		index = -1;
		amount = ci->Amount;

		while (amount > 0)
		{
			if (findNextCountable)
			{
				// 1-1. 이미 해당 아이템이 인벤토리 내에 존재하고, 개수 여유 있는지 검사
				index = FindCountableItemSlotIndex(ci->GetItemData(), index + 1);

				// 개수 여유있는 슬롯이 더이상 없다고 판단될 경우, 빈 슬롯부터 탐색 시작
				if (index == -1)
				{
					findNextCountable = false;
				}
				else
				{
					UCountableItem* OtherCI = Cast<UCountableItem>(items[index]);
					amount = OtherCI->AddAmountAndGetExcess(amount);
					UpdateSlot(index);
				}
			}
			else // 빈 슬롯 탐색
			{
				index = FindEmptySlotIndex(index + 1);

				// 빈 슬롯조차 없는 경우 종료
				if (index == -1)
				{
					ci->SetAmount(amount);
					break;
				}
				else // 빈 슬롯 발견 시, 슬롯에 아이템 추가 및 잉여량 계산
				{
					if (amount <= ci->MaxAmount())
					{
						items[index] = item;
						ci->SetAmount(amount);
					}
					else
					{
						// 새로운 아이템 생성
						UCountableItem* cloneCI = Cast<UCountableItem>(ci->GetItemData()->CreateItem());
						cloneCI->SetAmount(amount);
						items[index] = cloneCI;
					}

					// 남은 개수 계산
					amount = (amount > ci->GetItemData()->MaxAmount) ? (amount - ci->GetItemData()->MaxAmount) : 0;

					UpdateSlot(index);
				}
			}
		}
	}
	else
	{
		// 2-1. 1개만 넣는 경우, 간단히 수행
		if (amount == 1)
		{
			index = FindEmptySlotIndex();
			if (index != -1)
			{
				// 아이템을 생성하여 슬롯에 추가
				items[index] = item;
				amount = 0;

				UpdateSlot(index);
			}
		}

		//// 2-2. 2개 이상의 수량 없는 아이템을 동시에 추가하는 경우
		//index = -1;
		//for (; amount > 0; amount--)
		//{
		//	// 아이템 넣은 인덱스의 다음 인덱스부터 슬롯 탐색
		//	index = FindEmptySlotIndex(index + 1);

		//	// 다 넣지 못한 경우 루프 종료
		//	if (index == -1)
		//	{
		//		break;
		//	}

		//	// 아이템을 생성하여 슬롯에 추가
		//	items[index] = item;

		//	UpdateSlot(index);

		//}
	}

	return amount;
}

int32 UInventoryComponent::Add(UItemData* itemData, int amount)
{
	int32 index = 0;

	// 1. 수량이 있는 아이템
	if (UCountableItemData* ciData = Cast<UCountableItemData>(itemData))
	{
		
		bool findNextCountable = true;
		index = -1;

		while (amount > 0)
		{
			if (findNextCountable)
			{
				// 1-1. 이미 해당 아이템이 인벤토리 내에 존재하고, 개수 여유 있는지 검사
				index = FindCountableItemSlotIndex(ciData, index + 1);

				// 개수 여유있는 슬롯이 더이상 없다고 판단될 경우, 빈 슬롯부터 탐색 시작
				if (index == -1)
				{
					findNextCountable = false;
				}
				else
				{
					UCountableItem* ci = Cast<UCountableItem>(items[index]);
					amount = ci->AddAmountAndGetExcess(amount);

					UpdateSlot(index);
				}
			}
			else // 빈 슬롯 탐색
			{
				index = FindEmptySlotIndex(index + 1);

				// 빈 슬롯조차 없는 경우 종료
				if (index == -1)
				{
					// 월드 객체 스폰 

					break;
				}
				else // 빈 슬롯 발견 시, 슬롯에 아이템 추가 및 잉여량 계산
				{
					// 새로운 아이템 생성
					UCountableItem* ci = Cast<UCountableItem>(ciData->CreateItem());
					ci->SetAmount(amount);

					// 슬롯에 추가
					items[index] = ci;

					// 남은 개수 계산
					amount = (amount > ciData->MaxAmount) ? (amount - ciData->MaxAmount) : 0;
					
					UpdateSlot(index);
				}
			}
			
		}
	}
	else // 2. 수량이 없는 아이템
	{
		// 2-1. 1개만 넣는 경우, 간단히 수행
		if (amount == 1)
		{
			index = FindEmptySlotIndex();
			if (index != -1)
			{
				// 아이템을 생성하여 슬롯에 추가
				items[index] = itemData->CreateItem();
				amount = 0;

				UpdateSlot(index);
			}
		}

		// 2-2. 2개 이상의 수량 없는 아이템을 동시에 추가하는 경우
		index = -1;
		for (; amount > 0; amount--)
		{
			// 아이템 넣은 인덱스의 다음 인덱스부터 슬롯 탐색
			index = FindEmptySlotIndex(index + 1);

			// 다 넣지 못한 경우 루프 종료
			if (index == -1)
			{
				// 월드 객체 스폰 
				break;
			}

			// 아이템을 생성하여 슬롯에 추가
			items[index] = itemData->CreateItem();

			UpdateSlot(index);
			
		}
	}

	return amount;
}

int32 UInventoryComponent::FindCountableItemSlotIndex(UCountableItemData* target, int startIndex)
{
	for (int i = startIndex; i < Capacity; i++)
	{
		UItem* current = items[i];
		if (current == nullptr)
			continue;
		
		// 아이템 종류 일치, 개수 여유 확인
		if (UCountableItem* countableItem = Cast<UCountableItem>(current))
		{
			if (current->GetItemData()->ItemGrade == target->ItemGrade &&
				current->GetItemData()->ItemType == target->ItemType &&
				current->GetItemData()->Name == target->Name &&
				current->GetItemData()->IconTexture == target->IconTexture)
			{
				if (!countableItem->IsMax())
					return i;
			}
		}
		
	}

	return -1;
}

void UInventoryComponent::Remove(int index)
{
	if (!IsValidIndex(index))
		return;

	items[index] = nullptr;
	UpdateSlot(index);
}

void UInventoryComponent::RemoveCountableItem(int index, int count)
{
	if (items[index] == nullptr)
		return;
	UCountableItem* countableItem = Cast<UCountableItem>(items[index]);
	if (countableItem == nullptr)
		return;

	int32 total = countableItem->Amount - count;
	if (total < 0)
		return;
	else if (total == 0)
	{
		Remove(index);
	}
	else
	{
		countableItem->SetAmount(total);
		UpdateSlot(index);
	}
}

void UInventoryComponent::DropToWorld(int index, int count)
{
	if (items[index] == nullptr)
		return;
	
	UCountableItem* countableItem = Cast<UCountableItem>(items[index]);
	if (countableItem == nullptr)
		count = 1;
	else
		count = FMath::Clamp(count, 0, countableItem->Amount);

	//items[index]->SpawnWorldObject(count);
}

void UInventoryComponent::SeparateAmount(int32 from, int32 to, int count)
{
	// amount : 나눌 목표 수량
	
	if (!IsValidIndex(from))
		return;
	if (!IsValidIndex(to))
		return;

	UItem* _itemFrom = items[from];
	UItem* _itemTo = items[to];

	UCountableItem* ci = Cast<UCountableItem>(_itemFrom);

	// 조건 : A 슬롯 - 셀 수 있는 아이템 / B 슬롯 - Null
    // 조건에 맞는 경우, 복제하여 슬롯 B에 추가
	if (ci != nullptr && _itemTo == nullptr)
	{
		items[to] = ci->SeperateAndClone(count);

		TArray<int> arr;
		arr.Add(from);
		arr.Add(to);
		UpdateArraySlot(arr);
	}
}

void UInventoryComponent::Use(int index)
{
	if (items[index] == nullptr)
		return;

	if (IUseableItem* usableItem = Cast<IUseableItem>(items[index]))
	{
		bool succeed = usableItem->Use();

		if (succeed)
		{
			UpdateSlot(index);
		}
	}
	else if (UEquipmentItem* equipItem = Cast<UEquipmentItem>(items[index]))
	{
		EquipmentComponent->EquipEquipment(index, equipItem);
	}
}

void UInventoryComponent::TestItemSpawn(EItemType type, int index, int cnt)
{
	UItemData* item = UKRPGAssetManager::Get().GetNewItemData(type, index);
	if (item == nullptr)
		return;

	Add(item, cnt);
}

