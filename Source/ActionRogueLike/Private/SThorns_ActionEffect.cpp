// Fill out your copyright notice in the Description page of Project Settings.


#include "SThorns_ActionEffect.h"

#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "SGameplayFunctionLibrary.h"


USThorns_ActionEffect::USThorns_ActionEffect()
{
}

void USThorns_ActionEffect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	
		USAttributeComponent*AttributeComp = USAttributeComponent::GetAttribute(GetOwningComponent()->GetOwner());
		if(AttributeComp)
		{
			AttributeComp->OnHealthChange.AddDynamic(this, &USThorns_ActionEffect::OnHealthChanged);
		}
	
}

void USThorns_ActionEffect::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	USAttributeComponent*AttributeComp = USAttributeComponent::GetAttribute(GetOwningComponent()->GetOwner());
	if(AttributeComp)
    		{
    			AttributeComp->OnHealthChange.RemoveDynamic(this, &USThorns_ActionEffect::OnHealthChanged);
    		}	
	
}

void USThorns_ActionEffect::ExecutePeriodicEffect_Implementation(AActor* Instigator)
{


}

void USThorns_ActionEffect::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningCompo,
	float NewHealth, float Delta)
{
	//A que componente pertenecemos y luego a quien le pertenece ese comp
	AActor* OwningActor = GetOwningComponent()->GetOwner();
	if(Delta<=0.0f && OwningActor != InstigatorActor)
	{
		int32 ReflectedDmg = FMath::RoundToInt(Delta * ReflectFraction);
		if(ReflectedDmg == 0)
		{
			return;
		}
		ReflectedDmg = FMath::Abs(ReflectedDmg);
		//DrawDebugString(GetWorld(),InstigatorActor->GetActorLocation(),"THORNS",nullptr,FColor::Red);

        USGameplayFunctionLibrary::ApplyDamage(OwningActor,InstigatorActor,ReflectedDmg);
	}

}