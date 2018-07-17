// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
    ColliderComp = CreateDefaultSubobject<UBoxComponent>(TEXT("ColliderComp"));
    ColliderComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ColliderComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    ColliderComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    ColliderComp->SetBoxExtent(FVector(200));
    ColliderComp->SetHiddenInGame(false);
    ColliderComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::OnCompBeginOverlap);
    RootComponent = ColliderComp;

    DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
    DecalComponent->DecalSize = FVector(200);
    DecalComponent->SetupAttachment(RootComponent);
}

void AFPSExtractionZone::OnCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    auto myChar = Cast<AFPSCharacter>(OtherActor);

    if (!myChar)
        return;

    if (myChar->bIsCarryingObjective)
    {
        auto mode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
        if (mode)
        {
            mode->MissionComplete(myChar, true);
        }
    }
    else
    {
        UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
    }
}
