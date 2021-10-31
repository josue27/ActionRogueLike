// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpActor.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class UCurveFloat;
class UEnvQuery;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASGameModeBase();
	virtual  void StartPlay() override;

	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly,Category="AI")
	float SpawnTimerInterval = 2.0f;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UEnvQuery * SpawnBotQuery;
	UPROPERTY(EditDefaultsOnly,Category="AI")
	TSubclassOf<AActor> MinionClass;

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);
UPROPERTY(EditDefaultsOnly)
	UCurveFloat* DifficultyCurve;
	UFUNCTION()
	void SpawnTimerElapsed();

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION(Exec)
	void KillAll();
	
	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	protected:

	UPROPERTY(EditAnywhere,Category="PowerUps")
	UEnvQuery* PowerupSpawnQuery;

	UPROPERTY(EditAnywhere,Category="PowerUps")
	TArray<TSubclassOf<ASPowerUpActor>> PowerUpClasses;
	UPROPERTY(EditAnywhere,Category="PowerUps")
	int32 DesirePowerUpCount;
	UPROPERTY(EditAnywhere,Category="PowerUps")
	float RequiredPowerUpDistance = 100.0f;

	UFUNCTION()
	void OnPowerUpSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,EEnvQueryStatus::Type QueryStatus);
};
