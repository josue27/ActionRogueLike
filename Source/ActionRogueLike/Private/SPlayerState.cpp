// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

void ASPlayerState::ChangeCredits(int32 Amount)
{
	Credits += Amount;
}

void ASPlayerState::AddCredit(int32 Amount)
{
	if(Amount <= 0)
	{
		return;
	}
	Credits+=Amount;
	OnCreditsChanged.Broadcast(this,Credits,Amount);
}

bool ASPlayerState::RemoveCredit(int32 Amount)
{
	if(Amount < 0)
	{
		return false;
	}
	Credits-=Amount;
	OnCreditsChanged.Broadcast(this,Credits,-Amount);


	return true;
}

int32 ASPlayerState::GetCredits()
{
	return  Credits;
}

bool ASPlayerState::HasEnoughCredit(int32 ItemCost)
{
	return  Credits >= ItemCost;
}
