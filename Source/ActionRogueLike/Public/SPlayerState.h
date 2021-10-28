// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

	protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Scores")
    	int32 Credits = 10;
	public:

	

	UFUNCTION(BlueprintCallable,Category="Scores")
	void ChangeCredits(int32 Amount);

	UFUNCTION(BlueprintCallable,Category="Scores")
	int32 GetCredits();
	UFUNCTION(BlueprintCallable,Category="Scores")
	bool HasEnoughCredit(int32 ItemCost);
	
};
