// Fill out your copyright notice in the Description page of Project Settings.


#include "mover.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Pedestal.h"

// Sets default values for this component's properties
Umover::Umover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Umover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void Umover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    int OccupiedPedestals = APedestal::GetOccupiedPedestals(GetOwner()->GetWorld());


    TArray<AActor*> Pedestals;
    UGameplayStatics::GetAllActorsOfClass(GetOwner()->GetWorld(), APedestal::StaticClass(), Pedestals);
    int TotalPedestals = Pedestals.Num();
    

    if (OccupiedPedestals == TotalPedestals && TotalPedestals > 0)
    {
        MoveWall(DeltaTime);
    }

    APedestal* PedestalOne = FindPedestalWithTag("pedestal_gold");

    if (PedestalOne) 
    {
        if(GetOwner()->ActorHasTag("trap"))
        {
            if (PedestalOne->IsOccupied())
            {
                bDoorsAreDown = true;  
            }
            else
            {
                bDoorsAreDown = false; 
            }
            MoveWall(DeltaTime);
            UE_LOG(LogTemp, Display, TEXT("Moving wall to %s"), *TargetLocation.ToString());

        }
    }
    

}

void Umover::MoveWall(float DeltaTime)
{
    FVector CurrentLocation = GetOwner()->GetActorLocation();

    if (!bDoorsAreDown) 
    {
        TargetLocation = OriginalLocation + MoveOffset; 
    }
    else 
    {
        TargetLocation = OriginalLocation + MaxHeightOffset; 
    }

    float Speed = FVector::Distance(CurrentLocation, TargetLocation) / MoveTime;
    FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

    if (NewLocation.Z > OriginalLocation.Z + MaxHeightOffset.Z)
    {
        NewLocation.Z = OriginalLocation.Z + MaxHeightOffset.Z;
    }

    GetOwner()->SetActorLocation(NewLocation);
}


APedestal* Umover::FindPedestalWithTag(FName Tag)
{
    TArray<AActor*> Pedestals;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APedestal::StaticClass(), Pedestals);

    for (AActor* Actor : Pedestals)
    {
        if (Actor->ActorHasTag(Tag))
        {
            return Cast<APedestal>(Actor);
        }
    }
    return nullptr;
}

TArray<AActor*> Umover::FindActorsWithTag(FName Tag)
{
    TArray<AActor*> FoundActors;
    TArray<AActor*> AllActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

    for (AActor* Actor : AllActors)
    {
        if (Actor->ActorHasTag(Tag))
        {
            FoundActors.Add(Actor);
        }
    }
    return FoundActors;
}
