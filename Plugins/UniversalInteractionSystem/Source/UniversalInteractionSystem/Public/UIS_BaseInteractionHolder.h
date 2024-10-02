// Copyright Frytinhas UE Market 2024. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIS_BaseInteractionHolder.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "BaseWidgetInteractionHolder")
class UNIVERSALINTERACTIONSYSTEM_API UUIS_BaseInteractionHolder : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "References")
	class UUIS_Interactable* InteractableReference;

	UFUNCTION(Category = "Info", BlueprintPure, BlueprintCallable)
	float GetHoldProgress() const;
};
