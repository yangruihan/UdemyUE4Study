// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "Engine/World.h"


void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
    for (auto It = GetWorld()->GetPawnIterator(); It; ++It)
    {
        APawn* Pawn = It->Get();
        if (Pawn && Pawn->IsLocallyControlled())
        {
            Pawn->DisableInput(nullptr);
        }
    }
}
