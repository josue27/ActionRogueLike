// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SPowerUpActor.h"
#include "SPowerUpActor_Dash.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPowerUpActor_Dash : public ASPowerUpActor
{
	GENERATED_BODY()
	protected:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	public:
	UPROPERTY(EditDefaultsOnly,Category="PowerUp")
	TSubclassOf<USAction> Action;
};
