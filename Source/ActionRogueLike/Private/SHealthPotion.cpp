// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "IDetailTreeNode.h"
#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "SPlayerState.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	
}
// Called when the game starts or when spawned
void ASHealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn) 
{
	
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	if(AttributeComp && !AttributeComp->IsMaxHealth())
	{
		
		AttributeComp->ApplyHealthChange(this,HealthRecovery);
		HideAndCooldownPowerUp();
		ASPlayerState* PS = Cast<ASPlayerState>(InstigatorPawn->GetPlayerState());
		if(PS)
		{
			if(PS->HasEnoughCredit(ItemCost))
				PS->ChangeCredits(-ItemCost);
		}
		UE_LOG(LogTemp,Warning,TEXT("Health potion taken"));

	}else
	{
		UE_LOG(LogTemp,Warning,TEXT("Health potion cant be taken"));

	}
}

