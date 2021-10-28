// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "DrawDebugHelpers.h"
#include "SActionComponent.h"
#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "SGameplayFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(),true);

	if(ensureAlways(ParticleSpawn))
	{
		ASCharacter* Player = Cast<ASCharacter>(GetInstigator());
		if(Player)
		{
			UGameplayStatics::SpawnEmitterAttached(ParticleSpawn,Player->GetMesh(),NAME_None,Player->GetMesh()->GetSocketLocation("Muzzle_01"));
			UE_LOG(LogTemp,Warning,TEXT("Init particle spawneada"));
		}
	}
	
	
}

void ASMagicProjectile::Explode_Implementation()
{
	if(CameShake)
		UGameplayStatics::PlayWorldCameraShake(GetWorld(),CameShake,GetActorLocation(),1.0,1000.0f);
	
	Super::Explode_Implementation();
}

void ASMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	 /*if(OtherActor &&OtherActor!= GetInstigator())
	 {
	 	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	 	if(AttributeComp)
	 	{
	 		AttributeComp->ApplyHealthChange(GetInstigator(),DamageAmount);
		 
	 	
	 	}
		if(	USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(),OtherActor,DamageAmount,Hit))
		{
			
		}
	 }*/
	Explode();
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor!= GetInstigator())
	{
		// USActionComponent* ActionComponent = Cast<USActionComponent>(OtherActor->GetComponentByClass(USActionComponent::StaticClass()));
		// if(ActionComponent && ActionComponent->ActiveGameplayTags.HasTag(ParryTag))
		// {
		// 	ProjectileMovementComp->Velocity = -ProjectileMovementComp->Velocity;
		// 	SetInstigator(Cast<APawn>(OtherActor));
		// 	return;
		// }

		
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttribute(OtherActor);// Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if(AttributeComp)
		{
			AttributeComp->ApplyHealthChange(GetInstigator(),-DamageAmount);
			DrawDebugString(GetWorld(),GetActorLocation(),"HIT",nullptr,FColor::Red,4.0f,true);
			Explode();
		
		}
		// if(	USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(),OtherActor,DamageAmount,SweepResult))
		// {
		// 	Explode();
		// }
	}

}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


