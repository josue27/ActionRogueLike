// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SActionComponent.h"

#include "SAction.generated.h"

/**
 * 
 */
class UWorld;
UCLASS(Blueprintable)
class ACTIONROGUELIKE_API USAction : public UObject
{
	GENERATED_BODY()
protected:

	UFUNCTION(BlueprintCallable, Category="Tags")
	USActionComponent* GetOwningComponent() const;
	
	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FGameplayTagContainer BlockTags;

	bool bIsRunning;
	public:
	UFUNCTION(BlueprintCallable,Category="Action")
	bool IsRunning()const;
	
	UPROPERTY(EditDefaultsOnly,Category="Actions")
	FName ActionName;

	UFUNCTION(BlueprintNativeEvent,Category="Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Acttion")
	void StopAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent,Category="Acttion")

	bool CanStart(AActor* Instigator);

	UWorld* GetWorld() const override;
	
};
