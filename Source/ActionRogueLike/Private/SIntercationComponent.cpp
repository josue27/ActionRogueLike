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
	TraceRadius = 30.0f;
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
	FindBestInteractable();

}

void USIntercationComponent::FindBestInteractable()
{
	bool bDrawDebug = CVarDrawDebugInteraction.GetValueOnGameThread();
 //	FHitResult Hit;
 
 	FCollisionObjectQueryParams ObjectQueryParams;
 	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
 
 	AActor* MyOwner =  GetOwner();
 
 	FVector EyeLocation;
 	FRotator EyeRotator;
 	MyOwner->GetActorEyesViewPoint(EyeLocation,EyeRotator);
 	FVector End = EyeLocation + ( EyeRotator.Vector() * TraceDistance);
 
 //	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit,EyeLocation,End,ObjectQueryParams);

 	TArray<FHitResult>Hits;
 	FCollisionShape Shape;
 	Shape.SetSphere(TraceRadius);
 	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits,EyeLocation,End,FQuat::Identity,ObjectQueryParams,Shape);
 	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	//Clear before find it
	FocusedActor = nullptr;
 	for(FHitResult Hit: Hits)
 	{
 		if(bDrawDebug)
 		{
 			DrawDebugSphere(GetWorld(),Hit.ImpactPoint,TraceRadius,32,LineColor,false,2.0f);
      
 		}
      	
 		AActor* HitActor = Hit.GetActor();
 		if(HitActor)
 		{
 			if(HitActor->Implements<USGameplayInterface>())
 			{
 				FocusedActor = HitActor;
 				break;
 			}
 		}
 	}
	//Activate Widget
	if(FocusedActor)
	{
		if(DefaultWidgetInstance == nullptr && ensure(DefaultWidgetClass))
		{
			DefaultWidgetInstance = CreateWidget<USWorldUserWidget>(GetWorld(),DefaultWidgetClass);

		}
		if(DefaultWidgetInstance)
		{
			DefaultWidgetInstance->AttachedActor = FocusedActor;
			if(!DefaultWidgetInstance->IsInViewport())
			{
				DefaultWidgetInstance->AddToViewport();
			}
			
		}
	}else
	{
		if(DefaultWidgetInstance)
		{
			DefaultWidgetInstance->RemoveFromParent();
		}
	}
	
	//Debug
 	if(bDrawDebug)
 	{
 		DrawDebugLine(GetWorld(),EyeLocation,End,LineColor,false
         		,3.0f,0,2.0f);
 	}
 	
}

void USIntercationComponent::PrimaryInteract()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	if(FocusedActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Yellow,"InteractionComponent: No FocusActor to interact");
	}
	ISGameplayInterface::Execute_Interact(FocusedActor,MyPawn);
}