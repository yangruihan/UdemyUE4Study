// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHole();

protected:

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* MeshComp;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* SphereComp;

    UPROPERTY(EditDefaultsOnly, Category = "Values")
    float Force;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UFUNCTION()
    void OnSphereCompBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, 
                                  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
                                  bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
