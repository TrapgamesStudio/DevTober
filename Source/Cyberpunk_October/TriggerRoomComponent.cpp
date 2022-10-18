// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerRoomComponent.h"

#include "MainCharacter.h"

// Sets default values
ATriggerRoomComponent::ATriggerRoomComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("trigger"));
	m_TriggerComponent->SetupAttachment(m_MeshComponent);
}

// Called when the game starts or when spawned
void ATriggerRoomComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerRoomComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerRoomComponent::TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* character = Cast<AMainCharacter>(otherActor);

	if(character != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor(255,0,0),FString::Printf(TEXT("Character")));
	}
}

