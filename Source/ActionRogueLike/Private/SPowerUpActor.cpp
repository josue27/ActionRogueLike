// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpActor.h"

// Sets default values
ASPowerUpActor::ASPowerUpActor()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;
}


void ASPowerUpActor::ShowPowerUp()
{
	SetPowerUpSate(true);
}

void ASPowerUpActor::HideAndCooldownPowerUp()
{
	SetPowerUpSate(false);
	GetWorldTimerManager().SetTimer(TimeRespawn_Handler,this,&ASPowerUpActor::ShowPowerUp,RespawnTime);
}

void ASPowerUpActor::SetPowerUpSate(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	RootComponent->SetVisibility(false,true);
}

void ASPowerUpActor::Interact_Implementation(APawn* InstigatorPawn)
{
	
}




