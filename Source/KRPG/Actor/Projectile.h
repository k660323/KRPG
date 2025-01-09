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

	// ��ƼŬ ȿ�� �� ������
	UPROPERTY(EditAnywhere)
		TObjectPtr<UNiagaraSystem> ImpactEffect;

	// ������ �� ����
	UPROPERTY(EditAnywhere)
		TObjectPtr<USoundBase> ImpactSound;

	// ���󰥶� ������ ����
	UPROPERTY(EditAnywhere)
		TObjectPtr<USoundBase> LoopingSound;

	// ���� ���ְ� ���ִ� �༮(�Ŵ��� ����)
	UPROPERTY()
		TObjectPtr<UAudioComponent> LoopingSoundComponent;

public:
	// ������ ó�����ִ� ģ��

};
