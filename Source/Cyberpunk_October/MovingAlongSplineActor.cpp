// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingAlongSplineActor.h"

#include "MainCharacter.h"

// Sets default values
AMovingAlongSplineActor::AMovingAlongSplineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_splineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	m_splineComponent->SetupAttachment(GetRootComponent());

	m_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	m_MeshComponent->SetupAttachment(m_splineComponent);

	m_TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("trigger"));
	m_TriggerComponent->SetupAttachment(m_MeshComponent);
}

// Called when the game starts or when spawned
void AMovingAlongSplineActor::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerComponent->OnComponentBeginOverlap.AddDynamic(this,&AMovingAlongSplineActor::TriggerBeginOverlap);
	m_TriggerComponent->OnComponentEndOverlap.AddDynamic(this,&AMovingAlongSplineActor::TriggerEndOverlap);

	const FVector splineLocation = m_splineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	m_MeshComponent->SetWorldLocation(splineLocation);
	
	if(bAutoActivate)
		_TimeLine.Play();
}

// Called every frame
void AMovingAlongSplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(_TimeLine.IsPlaying())
	{
		_TimeLine.TickTimeline(DeltaTime);
	}

}

void AMovingAlongSplineActor::ProcessMovementTimeLine(float value)
{
	//value *= m_CurrentMovementSpeed; 
	const float splineLenght = m_splineComponent->GetSplineLength();

	/*GEngine->AddOnScreenDebugMessage( -1,100.0,FColor::Red, FString::Printf(TEXT("%f"),splineLenght ));
	GEngine->AddOnScreenDebugMessage( -1,100.0,FColor::Green, FString::Printf(TEXT("%f"),value  ));
	GEngine->AddOnScreenDebugMessage( -1,100.0,FColor::Blue, FString::Printf(TEXT("%f"),value * splineLenght  ));
	*/
	
	FVector currentSplineLocation = m_splineComponent->GetLocationAtDistanceAlongSpline(value * splineLenght,ESplineCoordinateSpace::World);
	FRotator currentSplineRotation = m_splineComponent-> GetRotationAtDistanceAlongSpline(value * splineLenght,ESplineCoordinateSpace::World);

	m_MeshComponent->SetWorldLocation(currentSplineLocation);
	m_MeshComponent->SetWorldRotation(currentSplineRotation);

	currentSplineRotation.Pitch = 0.0f;
	
}

void AMovingAlongSplineActor::OnEndMovementTimeLine()
{
	GEngine->AddOnScreenDebugMessage( -1,100.0,FColor::Red, FString::Printf(TEXT("test") ));

	if(bReverseOnEndtimeLine)
		_TimeLine.Reverse();
	else if(bRestartOnEndTimeLine)
		_TimeLine.PlayFromStart();
}

/**
 * @brief  Cette méthode s'éxecutera lorsque le personnage rentrera dans le trigger trigger.
 * Elle assignera a la timeline différentes méthode puis les executera.
 * @param OverlappedComponent 
 * @param otherActor 
 * @param otherComponent 
 * @param otherBodyIndex 
 * @param bFromSweep 
 * @param SweepResult 
 */
void AMovingAlongSplineActor::TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
                                                  UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*AMainCharacter* character = Cast<AMainCharacter>(otherActor);

	if(character != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor(255,0,0),FString::Printf(TEXT("Character")));
	}
	FOnTimelineFloat progressFunction;																					//
	progressFunction.BindUFunction(this,TEXT("ProcessMovementTimeLine"));							// Set up une méthode qui s'executera lorsque la timeline est en marche
	_TimeLine.AddInterpFloat(m_MovementCurve,progressFunction);															//

	FOnTimelineEvent OnTimelineFinishedFunction;																		//
	OnTimelineFinishedFunction.BindUFunction(this,TEXT("OnEndMovementTimeLine"));					// Set Up une méthode qui s'executera a la fin de la timeline
	_TimeLine.SetTimelineFinishedFunc(OnTimelineFinishedFunction);														//

	_TimeLine.SetTimelineLength(TL_LastKeyFrame);																		// set la fin de la timeline a la dernière keyframe
	_TimeLine.Play();*/
}


void AMovingAlongSplineActor::TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int32 otherBodyIndex)
{
	/*if(!_TimeLine.IsReversing())
		_TimeLine.Reverse();*/
}

void AMovingAlongSplineActor::MovingForward()
{
	FOnTimelineFloat progressFunction;																					//
	progressFunction.BindUFunction(this,TEXT("ProcessMovementTimeLine"));							// Set up une méthode qui s'executera lorsque la timeline est en marche
	_TimeLine.AddInterpFloat(m_MovementCurve,progressFunction);															//
	
	/*FOnTimelineEvent OnTimelineFinishedFunction;																		//
	OnTimelineFinishedFunction.BindUFunction(this,TEXT("OnEndMovementTimeLine"));					// Set Up une méthode qui s'executera a la fin de la timeline
	_TimeLine.SetTimelineFinishedFunc(OnTimelineFinishedFunction);				*/										//

	_TimeLine.SetTimelineLength(TL_LastKeyFrame);																		// set la fin de la timeline a la dernière keyframe
	_TimeLine.Play();
}

void AMovingAlongSplineActor::MovingBackward()
{
//	if(!_TimeLine.IsReversing())
		_TimeLine.Reverse();
}

void AMovingAlongSplineActor::FastForward()
{
	MovementAcceleration();
	MovingForward();
}

void AMovingAlongSplineActor::FastBackward()
{
	FastRevertMovement();
	MovingBackward();
}

void AMovingAlongSplineActor::Goforward()
{
	NormalMovement();
	MovingForward();
}

void AMovingAlongSplineActor::GoBackward()
{
	NormalMovement();
	MovingBackward();
}

void AMovingAlongSplineActor::StopMoving()
{
	_TimeLine.Stop();
}

void AMovingAlongSplineActor::ForceResetPosition()
{
	ProcessMovementTimeLine(0);
}

void AMovingAlongSplineActor::MovementAcceleration()
{
	m_CurrentMovementSpeed = m_FastSpeed;
}

void AMovingAlongSplineActor::FastRevertMovement()
{
	m_CurrentMovementSpeed = m_FastRevertSpeed;
}

void AMovingAlongSplineActor::NormalMovement()
{
	m_CurrentMovementSpeed = m_MovementSpeed;
}

void AMovingAlongSplineActor::ResetPosition()
{
	FastRevertMovement();
	MovingBackward();
}






