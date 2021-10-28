// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectile.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
ASProjectile::ASProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionObjectType(ECC_WorldStatic);
	SphereComp->SetCollisionObjectType(ECC_Pawn);
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetupAttachment(SphereComp);
	
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovementComp->InitialSpeed =1000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(SphereComp);

}

// Called when the game starts or when spawned
void ASProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(),true);
	SphereComp->OnComponentHit.AddDynamic(this,&ASProjectile::OnActorHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ASProjectile::OnActorOverlap);

}

void ASProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
}
void ASProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}
void ASProjectile::Explode_Implementation()
{
	if(ensure(!IsPendingKill()))
	{
		if(ensure(ImpactVFX))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactVFX,GetActorLocation(),GetActorRotation());
		}
		if(ensureAlways(ImpactSFX))
		{
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(),ImpactSFX,GetActorLocation(),GetActorRotation());
		}
		Destroy();
	}
	
}

// Called every frame
void ASProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

