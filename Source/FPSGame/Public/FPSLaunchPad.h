// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UStaticMeshComponent;
class UDecalComponent;
class UBoxComponent;

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:

    UPROPERTY(VisibleAnyWhere, Category = "Components")
    UStaticMeshComponent* MeshComp;

    UPROPERTY(VisibleAnyWhere, Category = "Components")
    UStaticMeshComponent* TopMeshComp;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UBoxComponent* OverlapComp;

    UPROPERTY(EditDefaultsOnly, Category = "Values")
    float LaunchStrength;

    UPROPERTY(EditDefaultsOnly, Category = "Values")
    float LaunchPitchAngle;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlapCompBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, 
                                   class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
                                   bool bFromSweep, const FHitResult & SweepResult);
};
