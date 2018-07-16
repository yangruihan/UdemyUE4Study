// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPawnSensingComponent* SensingComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UFUNCTION()
    void  OnSeePawn(APawn* Pawn);

    UFUNCTION()
    void OnHeardNoise(APawn* Pawn, const FVector& Location, float Volume);

    FRotator OriginRotator;
    FTimerHandle TimerHanlder_ResetRotation;

    UFUNCTION()
    void OnTimerResetRotation();

public:
    virtual void Tick(float DeltaSeconds) override;
};
