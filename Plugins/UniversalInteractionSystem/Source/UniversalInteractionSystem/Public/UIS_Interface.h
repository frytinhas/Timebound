// // Copyright Frytinhas UE Market 2024. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UIS_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UUIS_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNIVERSALINTERACTIONSYSTEM_API IUIS_Interface
{
	GENERATED_BODY()

public:
	/*
	 * End location need be equal to direction of trace
	 *		Example: EndLocation = Camera->GetForwardVector();
	 * Start location need be equal camera location
	 *		Example: return Camera->GetComponentLocation();
	 * * This function only used when you are using TraceType = UIS.Mode.ScreenCenter
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Essential")
	void GetStartLocationAndEndLocation(FVector& StartLocation, FVector& EndLocation);
};
