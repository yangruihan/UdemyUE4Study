// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    RootComponent = MeshComp;

    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    SphereComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();

    MeshComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OnSphereCompBeginOverlap);
}

void ABlackHole::OnSphereCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && !OtherActor->Tags.Contains(FName("SingularityExempt")))
    {
        OtherActor->Destroy();
    }
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TArray<UPrimitiveComponent*> OverlappingComps;
    SphereComp->GetOverlappingComponents(OverlappingComps);

    for (auto i = 0; i < OverlappingComps.Num(); i++)
    {
        auto PrimCop = OverlappingComps[i];

        if (PrimCop && PrimCop->GetOwner() != this
            && PrimCop->IsSimulatingPhysics()
            && !PrimCop->ComponentTags.Contains(FName("SingularityExempt")))
        {
            const auto SphereRadius = SphereComp->GetScaledSphereRadius();
            PrimCop->AddRadialForce(GetActorLocation(), SphereRadius, -Force, RIF_Constant, true);
        }
    }
}
