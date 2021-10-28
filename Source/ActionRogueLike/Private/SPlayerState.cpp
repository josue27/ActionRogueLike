// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

void ASPlayerState::ChangeCredits(int32 Amount)
{
	Credits += Amount;
}

int32 ASPlayerState::GetCredits()
{
	return  Credits;
}

bool ASPlayerState::HasEnoughCredit(int32 ItemCost)
{
	return  Credits >= ItemCost;
}
