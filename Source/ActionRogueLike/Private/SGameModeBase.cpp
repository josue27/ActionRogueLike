// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"

#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "SPlayerState.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"),true,TEXT("Enable spawning of bots via timer"),ECVF_Cheat);

ASGameModeBase::ASGameModeBase()
{
	//PlayerStateClass = ASPlayerState::StaticClass();
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots,this,&ASGameModeBase::SpawnTimerElapsed,SpawnTimerInterval,true);

}


void ASGameModeBase::SpawnTimerElapsed()
{
	if(!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp,Warning,TEXT("Bot spawning disable via cvar 'CVarSpawnBots'"));
		return;
	}
	int32 NrOfAliveBots = 0;
	//TActorIterator es un poco mas rapido que GetAllClasseOfType
	for(TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)
	{
		ASAICharacter* Bot = *It;
		USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttribute(Bot);
		if(ensure(AttributeComponent) && AttributeComponent->IsAlive())
		{
			NrOfAliveBots++;
		}
		
	}
	UE_LOG(LogTemp, Log,TEXT("Found %i alive bots"),NrOfAliveBots);
	float MaxBotCount = 10;
	if(DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}
	

	if(NrOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log,TEXT("At Maximum bot capacity"));

		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery,this, EEnvQueryRunMode::RandomBest5Pct,nullptr);
	if(ensure(QueryInstance))
	{
			QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this,&ASGameModeBase::OnQueryCompleted);

	}
	
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp,Warning,TEXT("Spawn bot EQS failed!"));
		return;
	}
	

	
	TArray<FVector>Locations = 	QueryInstance->GetResultsAsLocations();
	if(Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0],FRotator::ZeroRotator);
		DrawDebugSphere(GetWorld(),Locations[0],30.0f,6,FColor::Blue);
	}
}

void ASGameModeBase::KillAll()
{
	for(TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)
	{
		ASAICharacter* Bot = *It;
		USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttribute(Bot);
		if(ensure(AttributeComponent) && AttributeComponent->IsAlive())
		{
			AttributeComponent->Kill(this);
		}
		
	}
}

void ASGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	ASCharacter* Player = Cast<ASCharacter>(VictimActor);
	if(Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;//es imoprtante que sea local porque en multiplayer todos usarian la misma var
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this,"RespawnPlayerElapsed",Player->GetController());
		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay,Delegate,RespawnDelay,false);

		UE_LOG(LogTemp,Log,TEXT("OnActorKilled: %s was killed by %s"),*GetNameSafe(VictimActor),*GetNameSafe(Killer));
		return;
	}
	ASAICharacter* Bot = Cast<ASAICharacter>(VictimActor);
	if(Bot)
	{
		ASPlayerState* PS = Cast<ASPlayerState>(PlayerStateClass);
		if(PS)
		{
			PS->ChangeCredits(20);
		}
	}
}

void ASGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if(ensure(Controller))
	{
		Controller->UnPossess();//esto hace que tengamos una nueva copia del player de lo contrario mueve(sigue usando) el viejo
		RestartPlayer(Controller);//funcion de UE4
	}
}
