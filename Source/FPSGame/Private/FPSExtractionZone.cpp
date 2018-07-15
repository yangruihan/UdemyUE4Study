// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"

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
}

void AFPSExtractionZone::OnCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Log, TEXT("AFPSExtractionZone OnCompBeginOverlap"));
}
