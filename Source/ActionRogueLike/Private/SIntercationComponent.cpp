// Fill out your copyright notice in the Description page of Project Settings.


#include "SIntercationComponent.h"

#include <Shape.h>

#include "DrawDebugHelpers.h"
#include "SGameplayInterface.h"

static TAutoConsoleVariable<bool> CVarDrawDebugInteraction(TEXT("su.DrawDebugInteraction"),false,TEXT("Enable spawning of bots via timer"),ECVF_Cheat);

// Sets default values for this component's properties
USIntercationComponent::USIntercationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USIntercationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USIntercationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USIntercationComponent::PrimaryInteract()
{
	bool bDrawDebug = CVarDrawDebugInteraction.GetValueOnGameThread();
//	FHitResult Hit;
	FVector Start;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner =  GetOwner();

	FVector EyeLocation;
	FRotator EyeRotator;
	MyOwner->GetActorEyesViewPoint(EyeLocation,EyeRotator);
	FVector End = EyeLocation + ( EyeRotator.Vector() * 1000.0f);

//	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit,EyeLocation,End,ObjectQueryParams);
	float Radius =30.0f;
	TArray<FHitResult>Hits;
	FCollisionShape Shape;
	Shape.SetSphere(30.0f);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits,EyeLocation,End,FQuat::Identity,ObjectQueryParams,Shape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for(FHitResult Hit: Hits)
	{
		if(bDrawDebug)
		{
			DrawDebugSphere(GetWorld(),Hit.ImpactPoint,Radius,32,LineColor,false,2.0f);
     
		}
     	
		AActor* HitActor = Hit.GetActor();
		if(HitActor)
		{
			if(HitActor->Implements<USGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				ISGameplayInterface::Execute_Interact(HitActor,MyPawn);
				break;
			}
		}
	}
	




	if(bDrawDebug)
	DrawDebugLine(GetWorld(),EyeLocation,End,LineColor,false
		,3.0f,0,2.0f);
}