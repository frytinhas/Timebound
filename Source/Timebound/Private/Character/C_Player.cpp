// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_Player.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UIS_Interactor.h"
#include "GameplayTagContainer.h"
#include "UIS_Interactable.h"
#include "Camera/CameraComponent.h"
#include "Character/C_CharacterInterface.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/HUD.h"

// Sets default values
AC_Player::AC_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	
	InteractorComponent = CreateDefaultSubobject<UUIS_Interactor>(TEXT("Interactor Component"));
	InteractorComponent->TraceType = FGameplayTag::RequestGameplayTag("UIS.Mode.ScreenCenter");
}

// Called when the game starts or when spawned
void AC_Player::BeginPlay()
{
	Super::BeginPlay();
	
	IsWalking();
	OnTakeAnyDamage.AddUniqueDynamic(this, &AC_Player::OnReceiveAnyDamage);
}

// Called every frame
void AC_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (MoveForwardBackAction)
	{
		Input->BindAction(MoveForwardBackAction, ETriggerEvent::Triggered, this, &AC_Player::Input_MoveForwardBack);
	}
	if (MoveRightLeftAction)
	{
		Input->BindAction(MoveRightLeftAction, ETriggerEvent::Triggered, this, &AC_Player::Input_MoveRightLeft);
	}
	if (JumpAction)
	{
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &AC_Player::Input_Jump);
	}
	if (CrouchAction)
	{
		Input->BindAction(CrouchAction, ETriggerEvent::Started, this, &AC_Player::Input_Crouch);
	}
	if (InteractionAction)
	{
		Input->BindAction(InteractionAction, ETriggerEvent::Started, this, &AC_Player::Input_StartInteraction);
		Input->BindAction(InteractionAction, ETriggerEvent::Completed, this, &AC_Player::Input_EndInteraction);
	}
}

void AC_Player::Input_MoveForwardBack(const FInputActionValue& Value)
{
	AddMovementInput(GetActorForwardVector(), Value.Get<float>());
}

void AC_Player::Input_MoveRightLeft(const FInputActionValue& Value)
{
	AddMovementInput(GetActorRightVector(), Value.Get<float>());
}

void AC_Player::Input_Jump(const FInputActionValue& Value)
{
	Jump();
}

void AC_Player::Input_Crouch(const FInputActionValue& Value)
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void AC_Player::Input_StartInteraction(const FInputActionValue& Value)
{
	if (InsuredItem && !InteractorComponent->GetNearbyInteractable())
	{
		UpdateInsuredItem(nullptr);
	}
	else
	{
		InteractorComponent->StartInteraction();
	}
}

void AC_Player::Input_EndInteraction(const FInputActionValue& Value)
{
	InteractorComponent->EndInteraction();
}

void AC_Player::GetStartLocationAndEndLocation_Implementation(FVector& StartLocation, FVector& EndLocation)
{
	StartLocation = CameraComponent->GetComponentLocation();
	EndLocation = CameraComponent->GetForwardVector();
}

void AC_Player::IsWalking()
{
	if (GetCharacterMovement()->IsWalking() && GetVelocity().Length() >= 300.0f)
	{
		const TArray<AActor*> ActorsToIgnore = {this};
		FHitResult HitResult;
		UKismetSystemLibrary::LineTraceSingle(this, GetActorLocation(), GetActorLocation() - GetActorUpVector() * 95.0f, TraceTypeQuery1, false, ActorsToIgnore,
			EDrawDebugTrace::None, HitResult, true);
		if (UPhysicalMaterial* PhysMaterial = HitResult.PhysMaterial.Get())
		{
			switch (PhysMaterial->SurfaceType)
			{
				case SurfaceType1:
					if (!FootstepSounds[0]) {return;}
					UGameplayStatics::PlaySoundAtLocation(this, FootstepSounds[0], GetActorLocation(), GetActorRotation());
					break;
				case SurfaceType2:
					if (!FootstepSounds[1]) {return;}
					UGameplayStatics::PlaySoundAtLocation(this, FootstepSounds[1], GetActorLocation(), GetActorRotation());
					break;
				case SurfaceType3:
					if (!FootstepSounds[2]) {return;}
					UGameplayStatics::PlaySoundAtLocation(this, FootstepSounds[2], GetActorLocation(), GetActorRotation());
					break;
				default:
					if (!FootstepSounds[0]) {return;}
					UGameplayStatics::PlaySoundAtLocation(this, FootstepSounds[0], GetActorLocation(), GetActorRotation());
					break;
			}
		}
		else
		{
			if (!FootstepSounds[0]) {return;}
			UGameplayStatics::PlaySoundAtLocation(this, FootstepSounds[0], GetActorLocation(), GetActorRotation());
		}
	}
	GetWorldTimerManager().SetTimer(FootstepTimerHandle, this, &AC_Player::IsWalking, bIsCrouched ? 0.5f : 0.3f, false);
}

void AC_Player::UpdateInsuredItem(AActor* NewInsuredItem, const bool bDefineInsteadAddOffset, const FTransform& Offset)
{
	if (IsValid(InsuredItem))
	{
		InsuredItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		
		if (UMeshComponent* ItemMesh = Cast<UMeshComponent>(InsuredItem->GetRootComponent()))
		{
			ItemMesh->SetCastShadow(true);
			ItemMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
			ItemMesh->SetSimulatePhysics(true);
		}

		if (UUIS_Interactable* Interactable = InsuredItem->FindComponentByClass<UUIS_Interactable>())
		{
			Interactable->bCanInteract = true;
		}
	}

	if (NewInsuredItem == InsuredItem || !NewInsuredItem)
	{
		InsuredItem = nullptr;
		return;
	}
	
	InsuredItem = NewInsuredItem;
	if (UMeshComponent* ItemMesh = Cast<UMeshComponent>(InsuredItem->GetRootComponent()))
	{
		ItemMesh->SetCastShadow(false);
		ItemMesh->SetSimulatePhysics(false);
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}
	
	InsuredItem->AttachToComponent(CameraComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	if (bDefineInsteadAddOffset)
	{
		InsuredItem->SetActorRelativeTransform(Offset);
	}
	else
	{
		InsuredItem->AddActorLocalTransform(Offset);
	}
}

void AC_Player::OnReceiveAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsValid(this))
	{
		bPendingDeath = true;

		if (GetClass()->ImplementsInterface(UC_CharacterInterface::StaticClass()))
		{
			IC_CharacterInterface::Execute_OnPlayerDeath(this);
		}
		
		APlayerController* Pc = Cast<APlayerController>(GetController());
		Pc->DisableInput(Pc);
		DisableInput(Pc);
		
		AHUD* PlayerHUD = Pc->GetHUD();
		if (PlayerHUD->GetClass()->ImplementsInterface(UC_CharacterInterface::StaticClass()))
		{
			IC_CharacterInterface::Execute_OnPlayerDeath(PlayerHUD);
		}
		
		GetWorldTimerManager().SetTimer(DeathTimerHandle, [this]
		{
			UKismetSystemLibrary::ExecuteConsoleCommand(this, "RestartLevel");
		}, 3.0f, false);
	}
}

