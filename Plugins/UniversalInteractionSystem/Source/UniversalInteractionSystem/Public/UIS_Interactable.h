// Copyright Frytinhas UE Market 2024. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "UIS_Interactable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, class UUIS_Interactor*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartDetection, UUIS_Interactor*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndDetection, UUIS_Interactor*, Interactor);

UCLASS(ClassGroup=("Universal Interaction System"), meta=(BlueprintSpawnableComponent, DisplayName = "Interactable"))
class UNIVERSALINTERACTIONSYSTEM_API UUIS_Interactable : public UWidgetComponent
{
	GENERATED_BODY()

#pragma region Variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIS|Interaction", ReplicatedUsing = "OnRep_bCanInteract")
	bool bCanInteract = true;

	// Check this if you want the interaction to be disabled after a valid interaction.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIS|Interaction")
	bool bDisableOnInteract = true;

	// Check this if you want the player to have to hold the interact button for a certain time until the interaction is performed.
	UPROPERTY(EditAnywhere, Category = "UIS|Interaction|Hold")
	bool bNeedHold = false;

	/*
	* Determine how long the player needs to hold the interaction button for the interaction to complete.
	* * Only valid if "NeedHold = true"
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UIS|Interaction|Hold")
	float HoldTargetValue = 0.4f;

	// Only valid if "NeedHold = true"
	UPROPERTY(BlueprintReadOnly, Category = "UIS|Interaction|Hold")
	float HoldProgress = 0.0f;

	// If the actor is closest to the player and is available for interaction, this variable will be true.
	UPROPERTY(BlueprintReadOnly, Category = "UIS|Interaction")
	bool bIsShowing = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UIS|Info")
	FText Name = FText::FromString("Name");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UIS|Info")
	FText Tooltip = FText::FromString("Tooltip");

#pragma endregion Variables

#pragma region Functions
protected:
	// Sets default values for this component's properties
	UUIS_Interactable();

	virtual void BeginPlay() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// You can override this function on child classes if you want to apply a custom logic
	virtual void Interact(UUIS_Interactor* Interactor);

	FTimerHandle ResetDetectionTimerHandle;
	void UpdateDetection(UUIS_Interactor* Interactor, const float& TurnOffTime);

	UPROPERTY(BlueprintAssignable, Category = "UIS|Essential")
	FOnInteract OnInteract;

	UPROPERTY(BlueprintAssignable, Category = "UIS|Essential")
	FOnStartDetection OnStartDetection;

	UPROPERTY(BlueprintAssignable, Category = "UIS|Essential")
	FOnEndDetection OnEndDetection;

	// Called when server change the value of "bCanInteract"
	UFUNCTION(BlueprintNativeEvent, DisplayName = "OnChangeCanInteract")
	void OnRep_bCanInteract();

	/*
	 * This function change the interactable name for all client's in game
	 * * Call this in Server!!!
	*/
	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable, Category = "UIS|Info", DisplayName = "SetInteractableNameForAll")
	void SetInteractableNameForAll_Multicast(const FText& NewName);

	/*
	 * This function change the interactable tooltip for all client's in game
	 * * Call this in Server!!!
	*/
	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable, Category = "UIS|Info", DisplayName = "SetInteractableTooltipForAll")
	void SetInteractableTooltipForAll_Multicast(const FText& NewTooltip);
#pragma endregion Functions
};
