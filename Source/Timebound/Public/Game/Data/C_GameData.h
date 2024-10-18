// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_GameData.generated.h"

class UMovieSceneSequencePlayer;

USTRUCT(Blueprintable, BlueprintType)
struct FCutsceneInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	UMovieSceneSequencePlayer* LevelSequence = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	APawn* Player = nullptr;

	UPROPERTY(BlueprintReadWrite, DisplayName = "View Target")
	AActor* CutsceneCamera = nullptr;

	UPROPERTY(BlueprintReadWrite)
	bool bAutoDestroyCameraOnFinish = true;

	UPROPERTY(BlueprintReadWrite)
	float StartDelay = 1.5;
	
	UPROPERTY(BlueprintReadWrite)
	bool bMovePlayerToCameraOnEnd = true;

	UPROPERTY(BlueprintReadWrite)
	bool bHideHUD = true;
};

USTRUCT(Blueprintable, BlueprintType)
struct FGameInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Future")
	bool bControlGateUnlocked = false;

	UPROPERTY(BlueprintReadWrite, Category = "Future")
	bool bPhoneBoothUnlocked = false;

	UPROPERTY(BlueprintReadWrite, Category = "Future")
	bool bFloorOpened = false;
};

UCLASS()
class TIMEBOUND_API UC_GameData : public UObject
{
	GENERATED_BODY()
	
};
