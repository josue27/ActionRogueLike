// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionEffect.h"


USActionEffect::USActionEffect()
{
	bAutoStart = true;
}

void USActionEffect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if(Duration>0.0f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this,"StopAction",Instigator);
		GetWorld()->GetTimerManager().SetTimer(DurtionHandle,Delegate,Duration,false);
	}
	if(Period>0.0f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this,"ExecutePeriodicEffect",Instigator);
		GetWorld()->GetTimerManager().SetTimer(PeriodHandle,Delegate,Period,true);
		
	}
}

void USActionEffect::StopAction_Implementation(AActor* Instigator)
{

	if(GetWorld()->GetTimerManager().GetTimerRemaining(PeriodHandle)<KINDA_SMALL_NUMBER)
	{
		ExecutePeriodicEffect(Instigator);
	}
	
	Super::StopAction_Implementation(Instigator);

	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);
	GetWorld()->GetTimerManager().ClearTimer(DurtionHandle);

	USActionComponent* ActionComp =Cast<USActionComponent>(Instigator);
	if(ActionComp)
	{
		ActionComp->RemoveAction(this);
	}

}


void USActionEffect::ExecutePeriodicEffect_Implementation(AActor* Instigator)
{
}
