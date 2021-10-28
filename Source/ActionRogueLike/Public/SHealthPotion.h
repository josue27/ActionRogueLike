// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpActor.h"
#include "SHealthPotion.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASHealthPotion : public ASPowerUpActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ASHealthPotion();

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Health Potion")
	UStaticMeshComponent* MeshComp;



	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Health Potion")
	float HealthRecovery = 10.0f;


	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimeHandler;


	
	void Interact_Implementation(APawn* InstigatorPawn) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
