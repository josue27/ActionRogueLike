// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SActionEffect.h"
#include "SProjectile.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"



UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public ASProjectile
{
	GENERATED_BODY()
	

protected:
	
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UParticleSystem* ParticleSpawn;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UCameraShakeBase> CameShake;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float DamageAmount = 20.0f;

	UFUNCTION()
	virtual void Explode_Implementation() override;

	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag ParryTag;
	public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USActionEffect> BurningActionClass;
};
