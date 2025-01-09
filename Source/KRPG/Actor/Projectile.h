// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS()
class KRPG_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

public:
	UFUNCTION()
		void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
		float LifeSpan = 15.f;

	bool bHit = false;

	// 파티클 효과 펑 터질때
	UPROPERTY(EditAnywhere)
		TObjectPtr<UNiagaraSystem> ImpactEffect;

	// 터질때 날 사운드
	UPROPERTY(EditAnywhere)
		TObjectPtr<USoundBase> ImpactSound;

	// 날라갈때 나오는 사운드
	UPROPERTY(EditAnywhere)
		TObjectPtr<USoundBase> LoopingSound;

	// 사운드 켜주고 꺼주는 녀석(매니져 느낌)
	UPROPERTY()
		TObjectPtr<UAudioComponent> LoopingSoundComponent;

public:
	// 데미지 처리해주는 친구

};
