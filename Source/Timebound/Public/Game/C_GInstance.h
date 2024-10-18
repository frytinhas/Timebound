// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/C_GameData.h"
#include "Engine/GameInstance.h"
#include "C_GInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishCurrentCutscene);

UCLASS()
class TIMEBOUND_API UC_GInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	FCutsceneInfo CurrentCutsceneInfo;

public:
	UPROPERTY(BlueprintReadWrite)
	FGameInfo GameInfo;
	
	UPROPERTY(BlueprintAssignable)
	FOnFinishCurrentCutscene OnFinishCurrentCutscene;
	
	UFUNCTION(BlueprintCallable)
	void PlayCutscene(const FCutsceneInfo& CutsceneInfo);
	
	UFUNCTION()
	void OnEndCutscene();
};
