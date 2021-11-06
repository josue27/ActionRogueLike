// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChange,AActor*,IntigatorActor,USAttributeComponent*,OwingComp ,float,NewHealth,float,Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRageChange,AActor*,InstigatorActor,USAttributeComponent*,OwningComp,float, NewRage,float,DeltaRage);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,Category="Attributes")
	static USAttributeComponent* GetAttribute(AActor* FromActor);

	UFUNCTION(BlueprintCallable,Category="Attributes", meta = (DisplayName ="IsAlive"))
	static bool IsActorAlive(AActor* Actor);
	// Sets default values for this component's properties
	USAttributeComponent();

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Attributes")
	float HealthMax = 100.0f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Attributes")
	float Health;
	

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Attributes")
	float RageMax = 100.0f;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Attributes")
	float Rage;
public:

	UFUNCTION(BlueprintCallable)
	bool Kill(AActor* InstigatorActor);
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChange OnHealthChange;

	UPROPERTY(BlueprintAssignable)
	FOnRageChange OnRageChange;

	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor,float Delta);

	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyRageChange(AActor* InstigatorActor,float DeltaRage);

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION()
	float GetCurrentHealth();
	UFUNCTION()
	bool IsMaxHealth();

	UFUNCTION()
	float GetCurrentRage();
	UFUNCTION()
	bool HasEnoughRage(float RageCost);
	UFUNCTION()
	void UseRage(float RageCost);
		
};
