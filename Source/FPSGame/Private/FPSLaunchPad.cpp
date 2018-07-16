// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchPad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "FPSCharacter.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    RootComponent = MeshComp;

    TopMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopMeshComp"));
    TopMeshComp->SetupAttachment(RootComponent);

    OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
    OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::OnOverlapCompBeginOverlap);
    OverlapComp->SetupAttachment(RootComponent);

    LaunchStrength = 1500.0f;
    LaunchPitchAngle = 35.0f;
}

// Called when the game starts or when spawned
void AFPSLaunchPad::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSLaunchPad::OnOverlapCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor)
        return;

    FRotator LaunchDirection = GetActorRotation();
    LaunchDirection.Pitch += LaunchPitchAngle;
    FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

    // if is player character
    auto myChar = Cast<AFPSCharacter>(OtherActor);
    if (myChar)
    {
        myChar->LaunchCharacter(LaunchVelocity, true, true);
        return;
    }

    if (OtherComp && OtherComp->IsSimulatingPhysics())
    {
        OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
    }
}
