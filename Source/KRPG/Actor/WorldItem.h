// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldItem.generated.h"

class UItem;
class UBoxComponent;

UCLASS()
class KRPG_API AWorldItem : public AActor
{
	GENERATED_BODY()
	
private:
	float yawSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* boxComponent;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		UItem* item;

public:	
	// Sets default values for this actor's properties
	AWorldItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
