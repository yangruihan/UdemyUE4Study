// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;
class ATargetPoint;
class AAIController;

UENUM(BlueprintType)
enum class EAIGuardState : uint8
{
    Idle,
    Suspicious,
    Alerted,
};

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

protected:

    UPROPERTY(ReplicatedUsing=OnRep_GuardState)
    EAIGuardState State;

    UFUNCTION()
    void OnRep_GuardState();

    void SetState(EAIGuardState NewState);

    UFUNCTION(BlueprintImplementableEvent, Category = "AI")
    void OnStateChanged(EAIGuardState NewState);

protected:

    UPROPERTY(EditAnywhere, Category = "AI")
    TArray<ATargetPoint*> TargetPoints;

    AAIController* AICtrl;

    ATargetPoint* CurrentTargetPoint;

    int TargetIndex;

    ATargetPoint* GetNextTargetPoint();

    bool MoveTo(ATargetPoint* TargetPoint);

    UFUNCTION()
    void OnMovementCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

public:
    virtual void Tick(float DeltaSeconds) override;
};
