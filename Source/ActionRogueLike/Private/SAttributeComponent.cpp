// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

#include "SGameModeBase.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"),1.0f,TEXT("Enable spawning of bots via timer"),ECVF_Cheat);

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	

	// ...
	Health = HealthMax;
}


bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	if(!GetOwner()->CanBeDamaged())
	{
		return  false;
	}
	ApplyHealthChange(InstigatorActor,-GetCurrentHealth());
	return  true;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if(!GetOwner()->CanBeDamaged())
	{
		return  false;
	}
	if(Delta < 0.0f)
	{
		float DeltaMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
		Delta *= DeltaMultiplier;
	}
	float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta,0.0f,HealthMax);
	float ActualDelta = Health - OldHealth;
	OnHealthChange.Broadcast(InstigatorActor,this,Health,ActualDelta);
	if(Health <=0.0f)
	{
		ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		if(GM)
		{
			GM->OnActorKilled(GetOwner(),InstigatorActor);
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("%s Hitted, changing health to %f"),*GetNameSafe(GetOwner()),Health);
	return  ActualDelta != 0;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

float USAttributeComponent::GetCurrentHealth()
{
	return Health;
}

bool USAttributeComponent::IsMaxHealth()
{
	return Health >= HealthMax;
}

USAttributeComponent* USAttributeComponent::GetAttribute(AActor* FromActor)
{
	if(FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}
	return  nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent* AttribComp = GetAttribute(Actor);
	if(AttribComp)
	{
		return AttribComp->IsAlive();
	}
	return  false;
}
