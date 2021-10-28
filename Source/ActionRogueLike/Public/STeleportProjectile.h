// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectile.h"
#include "STeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASTeleportProjectile : public ASProjectile
{
	GENERATED_BODY()
	public:
	ASTeleportProjectile();
	protected:

	FTimerHandle TimeHandler;
	
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleExplosion;

	virtual void BeginPlay() override;

	void ActivateTeleport();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float FlashTime = 1.0f;
};
