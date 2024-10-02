// Copyright Frytinhas UE Market 2024. All rights reserved.


#include "UIS_Interactable.h"
#include "Net/UnrealNetwork.h"
#include "UIS_Interactor.h"
#include "TimerManager.h"
#include "UIS_BaseInteractionHolder.h"


// Sets default values for this component's properties
UUIS_Interactable::UUIS_Interactable()
{
	// Define some settings
	SetIsReplicatedByDefault(true);
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawAtDesiredSize(true);
	SetWidgetClass(UUIS_BaseInteractionHolder::StaticClass());
	SetHiddenInGame(true);
}

void UUIS_Interactable::BeginPlay()
{
	Super::BeginPlay();

	SetHiddenInGame(true);
}

void UUIS_Interactable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UUIS_Interactable, bCanInteract);
}

void UUIS_Interactable::Interact(UUIS_Interactor* Interactor)
{
	if (bCanInteract)
	{
		if (bDisableOnInteract)
		{
			bCanInteract = false;
		}
		OnInteract.Broadcast(Interactor);
	}
}

void UUIS_Interactable::UpdateDetection(UUIS_Interactor* Interactor, const float& TurnOffTime)
{
	// Check if it can modify detection property's
	if (bCanInteract)
	{
		if (!bIsShowing)
		{
			bIsShowing = true;
			OnStartDetection.Broadcast(Interactor);
		}

		GetOwner()->GetWorldTimerManager().ClearTimer(ResetDetectionTimerHandle);
		GetOwner()->GetWorldTimerManager().SetTimer(ResetDetectionTimerHandle, [this, Interactor]
		{
			bIsShowing = false;
			OnEndDetection.Broadcast(Interactor);
		}, TurnOffTime, false);
	}
}

void UUIS_Interactable::SetInteractableNameForAll_Multicast_Implementation(const FText& NewName)
{
	Name = NewName;
}

void UUIS_Interactable::SetInteractableTooltipForAll_Multicast_Implementation(const FText& NewTooltip)
{
	Tooltip = NewTooltip;
}

void UUIS_Interactable::OnRep_bCanInteract_Implementation()
{
	
}
