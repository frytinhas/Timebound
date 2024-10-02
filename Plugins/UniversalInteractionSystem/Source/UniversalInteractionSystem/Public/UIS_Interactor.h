// Copyright Frytinhas UE Market 2024. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "UIS_Interactor.generated.h"

UCLASS(ClassGroup=("Universal Interaction System"), Blueprintable, meta=(BlueprintSpawnableComponent, DisplayName = "Interactor"))
class UNIVERSALINTERACTIONSYSTEM_API UUIS_Interactor : public UActorComponent
{
	GENERATED_BODY()

#pragma region Variables
public:
	// Last nearby interactive actors detected
	UPROPERTY(BlueprintReadOnly, Category = "UIS|Info")
	TArray<class UUIS_Interactable*> NearbyInteractables;

	UPROPERTY()
	AActor* Owner;

protected:
	// Change this variable on the server to modify whether this player can use UIS
	UPROPERTY(EditDefaultsOnly, Category = "UIS|Interaction|Trace")
	bool bInteractionActive = true;

public:
	/*
	 * Explore tags in "UIS.Mode" section
	 * * You can create new game tags in this section and use here, just override CustomTrace function to use ;)
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UIS|Interaction|Trace")
	FGameplayTag TraceType;

	/*
	 * If you are using TraceType = ScreenCenter, this is the distance of the trace from the center of the screen forward
	 * If you are using TraceType = Proximity, this is the radius of the detection sphere
	 * If you are using TraceType = Custom, you can use this variable as you wish.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UIS|Interaction|Trace")
	float TraceDistance = 500.0f;

	// Defines the collision profile of the trace, both sphere and line (You can use this on your Custom Trace Mode)
	UPROPERTY(EditDefaultsOnly, Category = "UIS|Interaction|Trace")
	TEnumAsByte<ETraceTypeQuery> TraceDetectionChannel = TraceTypeQuery1;

	// Enable this setting if you want to see Traces and detailed information about the UIS system.
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "UIS|Interaction|Trace")
	bool bDebug = false;

	// Define delay between detection traces
	UPROPERTY(EditDefaultsOnly, Category = "UIS|Interaction|Trace")
	float TraceTime = 0.03f;

private:
	UPROPERTY(Transient)
	UUIS_Interactable* InteractingComponent = nullptr;

#pragma endregion Variables

#pragma region Functions
	// Sets default values for this component's properties
	UUIS_Interactor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FTimerHandle GetInteractablesTimerHandle;
	// This function did the trace to get nearby interactables
	void TraceInteractables();

public:
	// Call this in the "Started" node if you are using the Enhanced Input System
	FTimerHandle HoldProgressTimerHandle;
	UFUNCTION(BlueprintCallable, Category = "UIS|Essential")
	void StartInteraction();

	UFUNCTION(Server, Reliable)
	void Interact_Server(UUIS_Interactable* NearbyInteractable);

	// Call this in the "Completed" node if you are using the Enhanced Input System
	UFUNCTION(BlueprintCallable, Category = "UIS|Essential")
	void EndInteraction();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UIS|Info")
	UUIS_Interactable* GetNearbyInteractable() const;

#pragma region Blueprintable
protected:
	UFUNCTION(BlueprintNativeEvent, Category = "UIS|Custom")
	TArray<FHitResult> CustomTrace(const float& CurrentTraceDistance = 500.0f,
	const TEnumAsByte<ETraceTypeQuery>& CurrentTraceDetectionChannel = TraceTypeQuery1, const float& CurrentTraceTime = 0.03f);

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UIS|Info")
	FORCEINLINE bool InteractionIsActive() const
	{
		return bInteractionActive;
	}

	// This functions also clear NearbyInteractables array
	UFUNCTION(BlueprintCallable, Category = "UIS|Essential")
	void SetInteractionActive(const bool& bActive);
		
	#pragma endregion Blueprintable

#pragma endregion Functions
};
