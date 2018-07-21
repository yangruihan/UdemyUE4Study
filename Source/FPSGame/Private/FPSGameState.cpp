// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "Engine/World.h"
#include "FPSPlayerController.h"


void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
    for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        auto PlayerCtrl = Cast<AFPSPlayerController>(It->Get());
        if (PlayerCtrl && PlayerCtrl->IsLocalController())
        {
            PlayerCtrl->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

            auto Pawn = PlayerCtrl->GetPawn();
            if (Pawn)
            {
                 Pawn->DisableInput(nullptr);
            }
        }
    }
}
