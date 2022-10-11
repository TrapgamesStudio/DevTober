// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "MovingAlongSplineActor.generated.h"

UCLASS()
class CYBERPUNK_OCTOBER_API AMovingAlongSplineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingAlongSplineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ProcessMovementTimeLine(float value);

	UFUNCTION()
	void OnEndMovementTimeLine();

	UFUNCTION()
	void TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex);

public :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Spline, meta = (AllowPrivateAccess = "true"))
	USplineComponent* m_splineComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Spline, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_MeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Spline, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* m_TriggerComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= Spline)
	UCurveFloat* m_MovementCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= Spline)
	bool bAutoActivate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= Spline, meta = (EditCondition = "!bRestartOnEndTimeLine"))
	bool bReverseOnEndtimeLine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= Spline, meta = (EditCondition = "!bReverseOnEndtimeLine"))
	bool bRestartOnEndTimeLine;

private:
	FTimeline _TimeLine;

	
};
