// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingTriggerComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEndingTriggerComponent::UEndingTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UEndingTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UEndingTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    AActor* Actor = GetEndingActor();

    if (Actor)
    {
        if (LevelToLoad != "")
        {
            UGameplayStatics::OpenLevel(GetWorld(), LevelToLoad);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("No level name set"));
        }
    }
}

AActor* UEndingTriggerComponent::GetEndingActor() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

    // Same as for (int32 i = 0; i < Actors.Num(); i++)
    for (AActor* Actor : Actors)
    {
        // Change "grabbed" to grabbed tag  from Grabber.cpp. Make a "GetGrabbedTag"
        if (Actor->ActorHasTag(EndingActorTag) && !Actor->ActorHasTag("Grabbed"))
        {
            return Actor;
        }
    }

    return nullptr;
}
