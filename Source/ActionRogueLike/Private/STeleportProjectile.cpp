// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ASTeleportProjectile::ASTeleportProjectile()
{
	ParticleExplosion = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleExplosion"));
}

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	AActor* Pawn = GetInstigator();
	SphereComp->IgnoreActorWhenMoving(Pawn,true);
	GetWorldTimerManager().SetTimer(TimeHandler,this,&ASTeleportProjectile::ActivateTeleport,FlashTime);
}

void ASTeleportProjectile::ActivateTeleport()
{
	GetWorldTimerManager().ClearTimer(TimeHandler);//te falto esto
	ProjectileMovementComp->StopMovementImmediately();//te falto esto
	if(ensureAlways(ParticleExplosion))
		ParticleExplosion->Activate();

	AActor* Pawn = GetInstigator();
	if(ensureAlways( Pawn))
	{
		FVector TeleportPos = GetActorLocation();
		Pawn->TeleportTo(TeleportPos,GetActorRotation(),false,false);
	}

}

