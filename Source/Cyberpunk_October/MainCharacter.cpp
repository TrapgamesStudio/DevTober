// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "PickupComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->AirControl = 0.2f;

	_FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	_FollowCamera->SetupAttachment(RootComponent);
	_FollowCamera->bUsePawnControlRotation = true;
}


// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse",this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse",this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("Move Right / Left",this,&AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Move Forward / Backward",this,&AMainCharacter::MoveForward);
	PlayerInputComponent->BindAction("interactButton",IE_Pressed,this, &AMainCharacter::InteractWithObject);
	
}

void AMainCharacter::InteractWithObject()
{
	FHitResult hitResult;

	FVector startTrace = _FollowCamera->GetComponentLocation();
	FVector forwardVector = _FollowCamera->GetForwardVector();
	FVector endTrace = startTrace + (forwardVector * m_RaycastDistance);

	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(this->GetOwner());
	
	if(GetWorld()->SweepSingleByChannel(hitResult,startTrace,endTrace,FQuat::Identity,ECC_Visibility,FCollisionShape::MakeSphere(m_CapsuleRadius),CollisionParameters))//LineTraceSingleByChannel(*hitResult,startTrace,endTrace,ECC_Visibility,CollisionParameters))
	{
		DrawDebugLine(GetWorld(), startTrace, endTrace, FColor(255,0,0),true);
		DrawDebugSphere(GetWorld(), hitResult.ImpactPoint,m_CapsuleRadius,2,FColor::Blue,true);
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor(255,0,0),FString::Printf(TEXT("You hit %s"),*hitResult.GetActor()->GetName()));
		UPickupComponent* pickupObject = Cast<UPickupComponent>(hitResult.GetActor());

		if(pickupObject != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor(255,0,0),FString::Printf(TEXT("You hit %s"),*hitResult.GetActor()->GetName()));
		}
		
	}
	
}


void AMainCharacter::MoveForward(float axis)
{
	FRotator rotation = Controller->GetControlRotation();
	FRotator yawRotation(0.0f, rotation.Yaw,0.0f);

	FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(direction,axis);
}

void AMainCharacter::MoveRight(float axis)
{
	FRotator rotation = Controller->GetControlRotation();
	FRotator yawRotation(0.0f, rotation.Yaw,0.0f);

	FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(direction,axis);
}
