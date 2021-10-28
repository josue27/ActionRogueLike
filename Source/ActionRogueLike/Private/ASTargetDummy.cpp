// Fill out your copyright notice in the Description page of Project Settings.


#include "ASTargetDummy.h"

// Sets default values
AASTargetDummy::AASTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComp"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void AASTargetDummy::BeginPlay()
{
	Super::BeginPlay();

	AttributeComponent->OnHealthChange.AddDynamic(this,&AASTargetDummy::OnHealthChanged);
	
}


// Called every frame
void AASTargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AASTargetDummy::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningCompo, float NewHealth,
	float Delta)
{
	if(Delta < 0)
	{
		MeshComponent->SetScalarParameterValueOnMaterials("TimeToHit",GetWorld()->TimeSeconds);
		
	}
}

