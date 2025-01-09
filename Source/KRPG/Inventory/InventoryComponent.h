// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemDataTable.h"
#include "InventoryComponent.generated.h"

class UInventoryWidget;
class UItem;
class UItemData;
class UCountableItemData;
class UEquipmentComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KRPG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// 수용 한도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		int32 Capacity = 0;

	// 초기 수용 한도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		int32 InitalCapacity = 32;

	// 최대 수용 한도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		int32 MaxCapacity = 64;

	// 연결된 인벤토리 UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInventoryWidget> InventoryWidget;

	// 아이템
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		TArray<UItem*> items;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UEquipmentComponent> EquipmentComponent;
public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// 유요한 인덱스인지 확인
	UFUNCTION(BlueprintCallable)
		bool IsValidIndex(int index);

	UFUNCTION(BlueprintCallable)
		int FindEmptySlotIndex(int startIndex = 0);

	UFUNCTION(BlueprintCallable)
		void UpdateAccessibleStatesAll();

	UFUNCTION(BlueprintCallable)
		bool HasItem(int index);

	UFUNCTION(BlueprintCallable)
		bool IsCountableItem(int index);

	UFUNCTION(BlueprintCallable)
		int GetCurrentAmount(int index);

	UFUNCTION(BlueprintCallable)
		UItemData* GetItemData(int index);

	UFUNCTION(BlueprintCallable)
		FString GetItemName(int index);

	UFUNCTION(BlueprintCallable)
		void UpdateSlot(int index);

	UFUNCTION(BlueprintCallable)
		void UpdateArraySlot(TArray<int>& indexs);

	UFUNCTION(BlueprintCallable)
		void RemoveIcon(int index);

	UFUNCTION(BlueprintCallable)
		void Swap(int indexA, int indexB);

	UFUNCTION(BlueprintCallable)
		void OverWriteItem(UItem* item, int index);

	UFUNCTION(BlueprintCallable)
		int32 AddItem(UItem* item);

	UFUNCTION(BlueprintCallable)
		int32 Add(UItemData* itemData, int amount = 1);

	UFUNCTION(BlueprintCallable)
		int32 FindCountableItemSlotIndex(UCountableItemData* target, int startIndex = 0);

	UFUNCTION(BlueprintCallable)
		void Remove(int index);

	UFUNCTION(BlueprintCallable)
		void RemoveCountableItem(int index, int count = 1);

	UFUNCTION(BlueprintCallable)
		void DropToWorld(int index, int count = 1);

	UFUNCTION(BlueprintCallable)
		void SeparateAmount(int32 from, int32 to, int count = 1);

	UFUNCTION(BlueprintCallable)
		void Use(int index);

	UFUNCTION(BlueprintCallable)
		void TestItemSpawn(EItemType type, int index, int cnt = 1);
};
