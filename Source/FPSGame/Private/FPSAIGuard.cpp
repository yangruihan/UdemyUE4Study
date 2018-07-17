// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "FPSGameMode.h"
#include "AIController.h"
#include "Engine/TargetPoint.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
    PrimaryActorTick.bCanEverTick = true;

    SensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComp"));
    SensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeePawn);
    SensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnHeardNoise);

    TargetIndex = -1;
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

    AICtrl = Cast<AAIController>(GetController());
    if (AICtrl)
    {
        AICtrl->ReceiveMoveCompleted.AddDynamic(this, &AFPSAIGuard::OnMovementCompleted);
    }

    OriginRotator = GetActorRotation();

    CurrentTargetPoint = GetNextTargetPoint();
    if (CurrentTargetPoint)
        MoveTo(CurrentTargetPoint);
}

void AFPSAIGuard::OnSeePawn(APawn* Pawn)
{
    if (!Pawn)
        return;

    // DrawDebugSphere(GetWorld(), Pawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10);

    SetState(EAIGuardState::Alerted);

    auto mode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
    if (mode)
    {
        mode->MissionComplete(Pawn, false);
    }

    AICtrl->StopMovement();
}

void AFPSAIGuard::OnHeardNoise(APawn* Pawn, const FVector& Location, float Volume)
{
    // DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Blue, false, 10);

    SetState(EAIGuardState::Suspicious);

    auto newRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location);
    newRotator.Pitch = 0;
    newRotator.Roll = 0;
    SetActorRotation(newRotator);

    GetWorldTimerManager().ClearTimer(TimerHanlder_ResetRotation);
    GetWorldTimerManager().SetTimer(TimerHanlder_ResetRotation, this, &AFPSAIGuard::OnTimerResetRotation, 3, false);

    AICtrl->StopMovement();
}

void AFPSAIGuard::OnTimerResetRotation()
{
    SetActorRotation(OriginRotator);

    SetState(EAIGuardState::Idle);

    if (CurrentTargetPoint)
        MoveTo(CurrentTargetPoint);
}

void AFPSAIGuard::SetState(EAIGuardState NewState)
{
    switch (State)
    {
    case EAIGuardState::Idle:
        if (NewState == EAIGuardState::Alerted || NewState == EAIGuardState::Suspicious)
        {
            State = NewState;
            OnStateChanged(NewState);
        }
        break;

    case EAIGuardState::Suspicious:
        if (NewState == EAIGuardState::Alerted || NewState == EAIGuardState::Idle)
        {
            State = NewState;
            OnStateChanged(NewState);
        }
        break;
    default:
        break;
    }
}

ATargetPoint* AFPSAIGuard::GetNextTargetPoint()
{
    auto num = TargetPoints.Num();

    if (num > 0)
    {
        TargetIndex++;

        if (num == 1 && TargetIndex == 1)
            return nullptr;

        return TargetPoints[TargetIndex % num];
    }

    return nullptr;
}

bool AFPSAIGuard::MoveTo(ATargetPoint* TargetPoint)
{
    return AICtrl->MoveToActor(TargetPoint, 30.0f) == EPathFollowingRequestResult::AlreadyAtGoal;
}

void AFPSAIGuard::OnMovementCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    if (Result == EPathFollowingResult::Type::Success)
    {
        CurrentTargetPoint = GetNextTargetPoint();
        if (CurrentTargetPoint)
            MoveTo(CurrentTargetPoint);
    }
}

void AFPSAIGuard::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
