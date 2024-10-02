// Copyright Frytinhas UE Market 2024. All rights reserved.


#include "UIS_BaseInteractionHolder.h"

#include "UIS_Interactable.h"

float UUIS_BaseInteractionHolder::GetHoldProgress() const
{
	if (InteractableReference)
	{
		return InteractableReference->HoldProgress / InteractableReference->HoldTargetValue;
	}
	return 0.0f; 
}
