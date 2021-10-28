// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoin.h"

#include "SCharacter.h"
#include "SPlayerState.h"

ASCoin::ASCoin()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void ASCoin::Interact_Implementation(APawn* InstigatorPawn)
{
	ASCharacter* PC = Cast<ASCharacter>(InstigatorPawn);
	if(PC)
	{
		ASPlayerState* PS = Cast<ASPlayerState>(PC->GetPlayerState());
		if(PS)
		{
			PS->ChangeCredits(Value);
			HideAndCooldownPowerUp();

		}
	}
}
