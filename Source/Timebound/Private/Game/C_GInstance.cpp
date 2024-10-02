// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/C_GInstance.h"
#include "MovieSceneSequencePlayer.h"
#include "Character/C_CharacterInterface.h"
#include "GameFramework/HUD.h"

void UC_GInstance::PlayCutscene(const FCutsceneInfo& CutsceneInfo)
{
	if (!CutsceneInfo.Player || !CutsceneInfo.LevelSequence) {return;}
	
	if (APlayerController* Pc = Cast<APlayerController>(CutsceneInfo.Player->GetController()))
	{
		CurrentCutsceneInfo = CutsceneInfo;
		
		CurrentCutsceneInfo.Player->DisableInput(Pc);
		Pc->DisableInput(Pc);

		if (Pc->GetHUD()->GetClass()->ImplementsInterface(UC_CharacterInterface::StaticClass()) && CurrentCutsceneInfo.bHideHUD)
		{
			IC_CharacterInterface::Execute_SetHUDVisibility(Pc->GetHUD(), true);
		}
		
		if (CurrentCutsceneInfo.StartDelay <= 0.0f)
		{
			if (CurrentCutsceneInfo.CutsceneCamera)
			{
				Pc->SetViewTarget(CurrentCutsceneInfo.CutsceneCamera);
			}
			
			CurrentCutsceneInfo.LevelSequence->Play();
			CurrentCutsceneInfo.LevelSequence->OnFinished.AddUniqueDynamic(this, &UC_GInstance::OnEndCutscene);
		}
		else
		{
			if (CurrentCutsceneInfo.CutsceneCamera)
			{
				Pc->SetViewTargetWithBlend(CurrentCutsceneInfo.CutsceneCamera, CurrentCutsceneInfo.StartDelay, VTBlend_EaseInOut, 2.1f);
			}
			
			FTimerHandle OnFinishViewTarget;
			Pc->GetWorldTimerManager().SetTimer(OnFinishViewTarget, [=, this]
			{
				CurrentCutsceneInfo.LevelSequence->Play();
				CurrentCutsceneInfo.LevelSequence->OnFinished.AddUniqueDynamic(this, &UC_GInstance::OnEndCutscene);
			}, CurrentCutsceneInfo.StartDelay + 0.1f, false);
		}
	}
}

void UC_GInstance::OnEndCutscene()
{
	OnFinishCurrentCutscene.Broadcast();
	OnFinishCurrentCutscene.Clear();
	
	if (!CurrentCutsceneInfo.Player) { return; }

	if (APlayerController* Pc = Cast<APlayerController>(CurrentCutsceneInfo.Player->GetController()))
	{
		CurrentCutsceneInfo.Player->EnableInput(Pc);
		Pc->EnableInput(Pc);

		Pc->SetViewTargetWithBlend(CurrentCutsceneInfo.Player, CurrentCutsceneInfo.StartDelay, VTBlend_EaseInOut, 2.1f);

		if (Pc->GetHUD()->GetClass()->ImplementsInterface(UC_CharacterInterface::StaticClass()) && CurrentCutsceneInfo.bHideHUD)
		{
			IC_CharacterInterface::Execute_SetHUDVisibility(Pc->GetHUD(), false);
		}
		
		if (CurrentCutsceneInfo.bMovePlayerToCameraOnEnd && CurrentCutsceneInfo.CutsceneCamera)
		{
			CurrentCutsceneInfo.Player->SetActorLocation(CurrentCutsceneInfo.CutsceneCamera->GetActorLocation() - FVector(0.0f, 0.0f, 45.0f));
			Pc->SetControlRotation(CurrentCutsceneInfo.CutsceneCamera->GetActorRotation());
		}
	}
	
	if (CurrentCutsceneInfo.bAutoDestroyCameraOnFinish && CurrentCutsceneInfo.CutsceneCamera)
	{	
		CurrentCutsceneInfo.CutsceneCamera->Destroy();
	}
}
