// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UAudioComponent;
class USoundBase;

UCLASS()
class ACTIONROGUELIKE_API ASProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASProjectile();
	
protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovementComp;
	

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditDefaultsOnly, Category= "Effects")
	UParticleSystem* ImpactVFX;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UAudioComponent* AudioComp;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	USoundBase* ImpactSFX;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual  void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Explode();
	
	public:	
	virtual void Tick(float DeltaTime) override;

};
