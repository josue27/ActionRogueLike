// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SPowerUpActor.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASPowerUpActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerUpActor();

protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere,Category="PowerUp")
	float RespawnTime = 10.0f;
	UPROPERTY(EditAnywhere,Category="PowerUp")
	int32 ItemCost = 10;

	FTimerHandle TimeRespawn_Handler;

	//FUNCTIONS
	UFUNCTION()
	void ShowPowerUp();

	UFUNCTION()
	void HideAndCooldownPowerUp();
	UFUNCTION()
	void SetPowerUpSate(bool bNewIsActive);

	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;


};
