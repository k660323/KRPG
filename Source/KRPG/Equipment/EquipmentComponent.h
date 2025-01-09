// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Define.h"
#include "EquipmentComponent.generated.h"

class UItem;
class UEquipmentItem;
class UInventoryComponent;
class UEquipmentWindowWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRPG_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipments", meta = (AllowPrivateAccess = "true"))
		TMap<EEquipType, UEquipmentItem*> equipItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UEquipmentWindowWidget> EquipmentWindowWidget;

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
		bool EquipEquipment(int32 index, UEquipmentItem* equipItem);

	UFUNCTION(BlueprintCallable)
		bool Unequip(UEquipmentItem* UnequipItem);

	UFUNCTION(BlueprintCallable)
		void UpdateUISlot(EEquipType type);

	UFUNCTION(BlueprintCallable)
		void UpdateStat(UEquipmentItem* equipItem, bool IsEquip);
};
