// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
    PrimaryActorTick.bCanEverTick = true;

    SensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComp"));
    SensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeePawn);
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSAIGuard::OnSeePawn(APawn* Pawn)
{
    if (!Pawn)
        return;

    UE_LOG(LogTemp, Log, TEXT("Seeeeee"));

    DrawDebugSphere(GetWorld(), Pawn->GetActorLocation(), 32.0f, 12, FColor::Blue, false, 10);
}

void AFPSAIGuard::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
