// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/WorldItem.h"
#include "Define.h"
#include "Components/BoxComponent.h"

// Sets default values
AWorldItem::AWorldItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	yawSpeed = 50.f;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	boxComponent->SetCollisionProfileName(TEXT("WorldItem"));

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	mesh->SetCollisionProfileName(TEXT("NoCollision"));
	mesh->SetupAttachment(boxComponent);
}

// Called when the game starts or when spawned
void AWorldItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWorldItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(FRotator(0.f, yawSpeed * DeltaTime, 0.f), true);
}

