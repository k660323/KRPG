// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Util.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UUtil : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Math")
	static FRotator LookAt(AActor* Origin, AActor* Target);

};
