// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "C_CharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UC_CharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TIMEBOUND_API IC_CharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	void OnPlayerDeath();

	UFUNCTION(BlueprintNativeEvent)
	void SetHUDVisibility(bool bHide = false);
};
