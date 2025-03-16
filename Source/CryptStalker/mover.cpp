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

    int OccupiedPedestals = APedestal::GetOccupiedPedestals(GetWorld());

    TArray<AActor*> Pedestals;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APedestal::StaticClass(), Pedestals);
    int TotalPedestals = Pedestals.Num();

    UE_LOG(LogTemp, Warning, TEXT("Total: %d, Occupied: %d"), TotalPedestals-2, OccupiedPedestals);

    if (OccupiedPedestals == TotalPedestals-2 && TotalPedestals > 0)
    {
        MoveWall(DeltaTime);
    }
}

void Umover::MoveWall(float DeltaTime)
{
    FVector CurrentLocation = GetOwner()->GetActorLocation();
    FVector TargetLocation = OriginalLocation + MoveOffset;
    float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;

    FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
    GetOwner()->SetActorLocation(NewLocation);
}
