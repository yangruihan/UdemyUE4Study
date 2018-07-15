// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::MissionComplete(APawn* pawn)
{
    if (pawn)
    {
        // Disable character input
        pawn->DisableInput(nullptr);

        // Change view target
        TArray<AActor*> ViewTargets;
        UGameplayStatics::GetAllActorsOfClass(this, ViewTargetClass, ViewTargets);

        if (ViewTargets.Num() > 0)
        {
            const auto viewTarget = ViewTargets[0];
            auto characterCtrl = Cast<APlayerController>(pawn->GetController());

            if (viewTarget && characterCtrl)
            {
                characterCtrl->SetViewTargetWithBlend(viewTarget, 0.8f, EViewTargetBlendFunction::VTBlend_Cubic);
            }
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("Viewtarget get error, please check ViewTargetClass set"));
        }
    }

    OnMissionCompleted(pawn);
}
