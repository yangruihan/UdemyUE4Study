// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameState.h"
#include "Engine/World.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

    GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::MissionComplete(APawn* InstigatorPawn, bool Success)
{
    if (InstigatorPawn)
    {
        // Change view target
        TArray<AActor*> ViewTargets;
        UGameplayStatics::GetAllActorsOfClass(this, ViewTargetClass, ViewTargets);

        if (ViewTargets.Num() > 0)
        {
            const auto viewTarget = ViewTargets[0];

            if (viewTarget)
            {
                for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
                {
                    auto PlayerCtrl = It->Get();
                    if (PlayerCtrl)
                    {
                        PlayerCtrl->SetViewTargetWithBlend(viewTarget, 0.8f, EViewTargetBlendFunction::VTBlend_Cubic);    
                    }
                }
            }
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("Viewtarget get error, please check ViewTargetClass set"));
        }
    }

    auto GS = GetGameState<AFPSGameState>();
    if (GS)
    {
        // Disable character input
        GS->MulticastOnMissionComplete(InstigatorPawn, Success);
    }

    OnMissionCompleted(InstigatorPawn, Success);
}
