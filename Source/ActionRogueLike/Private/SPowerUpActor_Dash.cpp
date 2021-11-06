// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpActor_Dash.h"

void ASPowerUpActor_Dash::Interact_Implementation(APawn* InstigatorPawn)
{
	if(InstigatorPawn)
	{
		USActionComponent* ActionComp = Cast<USActionComponent>(InstigatorPawn->GetComponentByClass(USActionComponent::StaticClass()));
		if(ActionComp)
		{
			ActionComp->AddAction(InstigatorPawn,Action);
		}
		UE_LOG(LogTemp,Warning,TEXT("Taking Dash powerup"));
	}
	
}
