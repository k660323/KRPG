// Fill out your copyright notice in the Description page of Project Settings.


#include "Util.h"

FRotator UUtil::LookAt(AActor* Origin, AActor* Target)
{
	FVector Direction = (Target->GetActorLocation() - Origin->GetActorLocation()).GetSafeNormal();
	float dotFwd = FVector::DotProduct(Origin->GetActorForwardVector(), Direction);
	float radiansFwd = FMath::Acos(dotFwd);
	float degreeFwd = FMath::RadiansToDegrees(radiansFwd);
	FVector crossFwd = FVector::CrossProduct(Origin->GetActorForwardVector(), Direction);
	
	// 왼쪽일 경우 각도를 -로 바꿔준다.
	if (crossFwd.Z < 0)
		degreeFwd *= -1;
	UE_LOG(LogTemp, Log, TEXT("Degree : %d"), degreeFwd);
	float dotUp = FVector::DotProduct(Origin->GetActorUpVector(), Direction);
	float radiansUp = FMath::Acos(dotUp);
	float degreeUp = FMath::RadiansToDegrees(radiansUp);
	FVector crossUp = FVector::CrossProduct(Origin->GetActorUpVector(), Direction);

	
	// 왼쪽일 경우 각도를 -로 바꿔준다.
	if (crossUp.Z < 0)
		degreeUp *= -1;

	return FRotator(degreeUp, degreeFwd, 0);
}
