// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"


bool USAction::CanStart_Implementation(AActor* Instigator)
{
	if(IsRunning())
	{
		return  false;
	}
	USActionComponent* Comp = GetOwningComponent();
	if(Comp->ActiveGameplayTags.HasAny(BlockTags))
	{
		return  false;
	}
	return  true;
}

void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);
	bIsRunning= true;
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopping: %s"), *GetNameSafe(this));

	ensureAlways(bIsRunning);
	
	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);
	bIsRunning = false;
}




UWorld* USAction::GetWorld() const
{
	//EL GetOuter() es valido porque en SActionComponent hay una funcion donde se llama AddAction
	//Y asi se crea un objeto donde se pasa a si mismo en "this"
	//lo hacemos porque puede ser que el objeto no tenga acceso a GetWorld, entonces llama a quien lo llamo y le pide
	//GetWorld()
	UActorComponent*Comp = Cast<UActorComponent> (GetOuter());
	if(Comp)
	{
		return  Comp->GetWorld();
	}
	return  nullptr;
}


USActionComponent* USAction::GetOwningComponent() const
{
	return Cast<USActionComponent>(GetOuter());
}

bool USAction::IsRunning() const
{
	return bIsRunning;
}
