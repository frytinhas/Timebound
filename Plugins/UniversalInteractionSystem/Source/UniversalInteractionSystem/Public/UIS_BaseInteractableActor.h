// Copyright Frytinhas UE Market 2024. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UIS_BaseInteractableActor.generated.h"

UCLASS(DisplayName = "BaseInteractableActor")
class UNIVERSALINTERACTIONSYSTEM_API AUIS_BaseInteractableActor : public AActor
{
	GENERATED_BODY()

#pragma region Components
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UUIS_Interactable> Interactable;

#pragma endregion Components

#pragma region Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Info", DisplayName = "Hide Widget On Detect")
	bool bHideWidget = true;

#pragma endregion Variables

#pragma region Functions
public:
	// Sets default values for this actor's properties
	AUIS_BaseInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void OnStartDetection(class UUIS_Interactor* Interactor);

	UFUNCTION()
	void OnEndDetection(UUIS_Interactor* Interactor);

#pragma endregion Functions
};
