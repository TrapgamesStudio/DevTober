// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingAlongSplineActor.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TriggerRoomComponent.generated.h"

UCLASS()
class CYBERPUNK_OCTOBER_API ATriggerRoomComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerRoomComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
		void TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Spline, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* m_TriggerComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Spline, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Spline, meta = (AllowPrivateAccess = "true"))
	TArray<AMovingAlongSplineActor*> m_RoomBP;
};
