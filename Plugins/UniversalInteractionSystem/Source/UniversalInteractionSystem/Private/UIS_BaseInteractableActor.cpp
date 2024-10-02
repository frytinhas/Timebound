// Copyright Frytinhas UE Market 2024. All rights reserved.


#include "UIS_BaseInteractableActor.h"
#include "UIS_BaseInteractionHolder.h"
#include "UIS_Interactable.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AUIS_BaseInteractableActor::AUIS_BaseInteractableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	SetRootComponent(Mesh);

	Interactable = CreateDefaultSubobject<UUIS_Interactable>(TEXT("Interactable Component"));
	Interactable->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AUIS_BaseInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	if (bHideWidget)
	{
		Interactable->SetHiddenInGame(true);
	}
	if (UUIS_BaseInteractionHolder* Widget = Cast<UUIS_BaseInteractionHolder>(Interactable->GetWidget()))
	{
		Widget->InteractableReference = Interactable;
	}
	else
	{
		throw"Add a widget child of BaseWidgetInteractionHolder in ALL Interactable Component's";
	}
	Interactable->OnStartDetection.AddDynamic(this, &AUIS_BaseInteractableActor::OnStartDetection);
	Interactable->OnEndDetection.AddDynamic(this, &AUIS_BaseInteractableActor::OnEndDetection);
}

void AUIS_BaseInteractableActor::OnStartDetection(UUIS_Interactor* Interactor)
{
	Interactable->SetHiddenInGame(false, false);
}

void AUIS_BaseInteractableActor::OnEndDetection(UUIS_Interactor* Interactor)
{
	if (bHideWidget)
	{
		Interactable->SetHiddenInGame(true, false);
	}
}

