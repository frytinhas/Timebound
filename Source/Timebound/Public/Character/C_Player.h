// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIS_Interface.h"
#include "GameFramework/Character.h"
#include "C_Player.generated.h"

class UCameraComponent;
class UUIS_Interactor;
class UInputMappingContext;
struct FInputActionValue;
class UInputAction;

UCLASS()
class TIMEBOUND_API AC_Player : public ACharacter, public IUIS_Interface
{
	GENERATED_BODY()

#pragma region Components
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UUIS_Interactor> InteractorComponent;

#pragma endregion Components
	
#pragma region Variables
private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveForwardBackAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveRightLeftAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* CrouchAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InteractionAction = nullptr;

	// Based on surface type
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	TArray<USoundWave*> FootstepSounds;

	FTimerHandle FootstepTimerHandle, DeathTimerHandle;

public:
	UPROPERTY(BlueprintReadWrite, Category = "References")
	AActor* InsuredItem = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Info")
	bool bPendingDeath = false;

private:
	FVector InsuredItemInitialScale;

#pragma endregion Variables
	
#pragma region Functions
	#pragma region Unreal Defaults
public:
	// Sets default values for this character's properties
	AC_Player();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	#pragma endregion Unreal Defaults

public:
	UFUNCTION(BlueprintCallable, Category = "Player")
	void UpdateInsuredItem(AActor* NewInsuredItem = nullptr, const bool bDefineInsteadAddOffset = true, const FTransform& Offset = FTransform());

private:
	#pragma region Inputs
	UFUNCTION()
	void Input_MoveForwardBack(const FInputActionValue& Value);

	UFUNCTION()
	void Input_MoveRightLeft(const FInputActionValue& Value);

	UFUNCTION()
	void Input_Jump(const FInputActionValue& Value);

	UFUNCTION()
	void Input_Crouch(const FInputActionValue& Value);
	
	UFUNCTION()
	void Input_StartInteraction(const FInputActionValue& Value);

	UFUNCTION()
	void Input_EndInteraction(const FInputActionValue& Value);

	virtual void GetStartLocationAndEndLocation_Implementation(FVector& StartLocation, FVector& EndLocation) override;

	#pragma endregion Inputs
	
	void IsWalking();
	
	UFUNCTION()
	void OnReceiveAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

#pragma endregion Functions
};
