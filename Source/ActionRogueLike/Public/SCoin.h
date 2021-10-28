// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SItemChest.h"
#include "SPowerUpActor.h"
#include "SCoin.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASCoin : public ASPowerUpActor
{
	GENERATED_BODY()
protected:
	
	ASCoin();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
		UStaticMeshComponent* Mesh;



	void Interact_Implementation(APawn* InstigatorPawn) override;


	public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Coin")
	int32 Value = 20;
	
};
