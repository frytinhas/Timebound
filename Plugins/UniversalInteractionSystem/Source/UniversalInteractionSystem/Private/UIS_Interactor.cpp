// Copyright Frytinhas UE Market 2024. All rights reserved.


#include "UIS_Interactor.h"

#include "UIS_Data.h"
#include "UIS_Interactable.h"
#include "UIS_Interface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UUIS_Interactor::UUIS_Interactor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	TraceType = FGameplayTag::RequestGameplayTag("UIS.Mode.Proximity");
	SetIsReplicatedByDefault(false);
}

// Called when the game starts
void UUIS_Interactor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	// Only did trace calc in client
	if (bInteractionActive && (Owner->GetLocalRole() == ROLE_AutonomousProxy || Owner->GetNetMode() == NM_Standalone))
	{
		TraceInteractables();
	}
}

void UUIS_Interactor::TraceInteractables()
{
	if (IsValid(Owner))
	{
		// Reset nearby interactables array
		NearbyInteractables.Reset();
		// Declare some variables
		const TArray<AActor*> ActorsToIgnore = {Owner};
		TArray<FHitResult> HitResults;
		
		//? Verify if TraceType tag matches with screen center tag
		if (TraceType.MatchesTag(UIS_Mode_ScreenCenter))
		{
			FHitResult HitResult;

			FVector StartLocation, EndLocation = FVector();
			if (Owner->GetClass()->ImplementsInterface(UUIS_Interface::StaticClass()))
			{
				IUIS_Interface::Execute_GetStartLocationAndEndLocation(Owner, StartLocation, EndLocation);
			}
			EndLocation *= TraceDistance;
			
			UKismetSystemLibrary::LineTraceSingle(this, StartLocation,
				StartLocation + EndLocation, TraceTypeQuery1, false, ActorsToIgnore, bDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitResult,
				false, FLinearColor::Red, FLinearColor::Green, TraceTime);

			//? Check if hit actor is valid and whether it has UIS_Interactable component
			if (HitResult.GetActor() && HitResult.GetActor()->GetComponentByClass<UUIS_Interactable>() &&
					HitResult.GetActor()->GetComponentByClass<UUIS_Interactable>()->bCanInteract)
			{
				NearbyInteractables.AddUnique(HitResult.GetActor()->GetComponentByClass<UUIS_Interactable>());
			}
		}
		//? Check if TraceType tag matches with proximity tag
		else if (TraceType.MatchesTag(UIS_Mode_Proximity))
		{
			UKismetSystemLibrary::SphereTraceMulti(this, Owner->GetActorLocation(),
				Owner->GetActorLocation(), TraceDistance, TraceTypeQuery1, false, ActorsToIgnore,
				bDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitResults,false, FLinearColor::Red, FLinearColor::Green, TraceTime);

			// Add all detected actors to array 
			for (const auto& h : HitResults)
			{
				//? Check if hit actor is valid and whether it has UIS_Interactable component
				if (h.GetActor() && h.GetActor()->GetComponentByClass<UUIS_Interactable>() &&
					h.GetActor()->GetComponentByClass<UUIS_Interactable>()->bCanInteract)
				{
					NearbyInteractables.AddUnique(h.GetActor()->GetComponentByClass<UUIS_Interactable>());
				}
			}
		}
		// Run custom trace mode (defined by user) in blueprint
		else
		{
			// Get hit result by your custom trace in blueprint
			HitResults = CustomTrace(TraceDistance, TraceDetectionChannel, TraceTime);
			
			// Add all detected actors to array
			for (const auto& h : HitResults)
			{
				//? Check if hit actor is valid and whether it has UIS_Interactable component
				if (h.GetActor() && h.GetActor()->GetComponentByClass<UUIS_Interactable>() &&
					h.GetActor()->GetComponentByClass<UUIS_Interactable>()->bCanInteract)
				{
					NearbyInteractables.AddUnique(h.GetActor()->GetComponentByClass<UUIS_Interactable>());
				}
			}
		}

		// Send detection notify to nearby interactable
		if (UUIS_Interactable* NearbyInteractable = GetNearbyInteractable())
		{
			NearbyInteractable->UpdateDetection(this, TraceTime);
		}
	}
	GetWorld()->GetTimerManager().SetTimer(GetInteractablesTimerHandle, this, &UUIS_Interactor::TraceInteractables, TraceTime, false);
}

void UUIS_Interactor::StartInteraction()
{
	if (const auto& NearbyInteractable = GetNearbyInteractable())
	{
		InteractingComponent = NearbyInteractable;
		if (InteractingComponent->bNeedHold)
		{
			GetWorld()->GetTimerManager().SetTimer(HoldProgressTimerHandle, [this]
			{
				if (InteractingComponent->HoldProgress < InteractingComponent->HoldTargetValue)
				{
					InteractingComponent->HoldProgress += GetWorld()->GetDeltaSeconds();
				}
				else
				{
					Interact_Server(InteractingComponent);
					GetWorld()->GetTimerManager().ClearTimer(HoldProgressTimerHandle);
					InteractingComponent->HoldProgress = 0.0f;
				} 
			}, GetWorld()->GetDeltaSeconds(), true);
		}
		else
		{
			Interact_Server(InteractingComponent);
		}
	}
}

void UUIS_Interactor::Interact_Server_Implementation(UUIS_Interactable* NearbyInteractable)
{
	if (NearbyInteractable)
	{
		NearbyInteractable->Interact(this);
	}
}

void UUIS_Interactor::EndInteraction()
{
	if (InteractingComponent)
	{
		InteractingComponent->HoldProgress = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(HoldProgressTimerHandle);
		InteractingComponent = nullptr;
	}
}

UUIS_Interactable* UUIS_Interactor::GetNearbyInteractable() const
{
	// Check if array is not empty
	if (IsValid(Owner) && !NearbyInteractables.IsEmpty())
	{
		//? Check if there is more than one element
		if (NearbyInteractables.Num() == 1)
		{
			return NearbyInteractables[0];
		}

		// Else...
		UUIS_Interactable* PvNearbyInteractable = nullptr;
		for (const auto& n : NearbyInteractables)
		{
			if (!PvNearbyInteractable)
			{
				PvNearbyInteractable = n;
			}
			else if (n->GetOwner()->GetDistanceTo(Owner) < PvNearbyInteractable->GetOwner()->GetDistanceTo(Owner))
			{
				PvNearbyInteractable = n;
			}
		}
		return PvNearbyInteractable;
	}
	// Else...
	return nullptr;
}

void UUIS_Interactor::SetInteractionActive(const bool& bActive)
{
	bInteractionActive = bActive;
	if (bInteractionActive)
	{
		TraceInteractables();
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(GetInteractablesTimerHandle);
		NearbyInteractables.Reset();
	}
}

#pragma region Blueprintable
TArray<FHitResult> UUIS_Interactor::CustomTrace_Implementation(const float& CurrentTraceDistance,
	const TEnumAsByte<ETraceTypeQuery>& CurrentTraceDetectionChannel, const float& CurrentTraceTime)
{
	TArray<FHitResult> HitResults;
	return HitResults;
}

#pragma endregion Blueprintable