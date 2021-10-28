// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosive_Barrel.h"

#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "SMagicProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosive_Barrel::ASExplosive_Barrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("ForceComp"));
	ForceComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void ASExplosive_Barrel::BeginPlay()
{
	Super::BeginPlay();
	MeshComp->OnComponentHit.AddDynamic(this,&ASExplosive_Barrel::Explode);
}

// Called every frame
void ASExplosive_Barrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASExplosive_Barrel::Explode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ASMagicProjectile* MagicProjectile = Cast<ASMagicProjectile>(OtherActor);
	if(ForceComp )
	{
		ForceComp->FireImpulse();

		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if(AttributeComp)
		{
			AttributeComp->ApplyHealthChange(this,-50.0f);
		}
		UE_LOG(LogTemp,Warning,TEXT("Barrel exploded"));
		UE_LOG(LogTemp,Warning,TEXT("Other Actor: %s at game time: %f"),*GetNameSafe(OtherActor),GetWorld()->TimeSeconds);
		FString CombineString = FString::Printf(TEXT("Hit at location %s"),*Hit.ImpactPoint.ToString());
		DrawDebugString(GetWorld(),Hit.ImpactPoint,CombineString,nullptr,FColor::Yellow,2.0f);
	}
}