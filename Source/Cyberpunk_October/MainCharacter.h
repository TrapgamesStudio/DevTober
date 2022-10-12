// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingAlongSplineActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()

class CYBERPUNK_OCTOBER_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Camera)
	UCameraComponent* _FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Raycast)
	float m_RaycastDistance = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Raycast)
	float m_CapsuleHalfHeight = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Raycast)
	float m_CapsuleRadius = 20.0f;

	AMovingAlongSplineActor* target;
	
	void MoveForward (float axis);
	void MoveRight (float axis);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	void InteractWithObject();
	void TriggerSensorialDance();
	
	void MoveObjectForward();
	void MoveObjectBackward();
	void StopMovement();
};
