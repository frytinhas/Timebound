// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "C_ItemsInterface.generated.h"

// Forward Declarations
class AC_Player;

// This class does not need to be modified.
UINTERFACE()
class UC_ItemsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TIMEBOUND_API IC_ItemsInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnPickupItem(AC_Player* Player);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDropItem(AC_Player* Player);
};
