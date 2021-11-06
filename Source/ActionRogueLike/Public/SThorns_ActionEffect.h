// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SActionEffect.h"
#include "SThorns_ActionEffect.generated.h"

class USAttributeComponent;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USThorns_ActionEffect : public USActionEffect
{
	GENERATED_BODY()
	protected:
	USThorns_ActionEffect();
	virtual void StartAction_Implementation(AActor* Instigator) override;
	virtual void StopAction_Implementation(AActor* Instigator) override;
	virtual void ExecutePeriodicEffect_Implementation(AActor* Instigator) override;
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningCompo, float NewHealth, float Delta);

	UPROPERTY(EditDefaultsOnly,Category="Actions")
	float ReflectFraction = 0.2f;
};



