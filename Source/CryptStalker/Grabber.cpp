// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Pedestal.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* Handle = CreateHandle();
	if (!Handle) return;
	FVector TarhetLocation = GetComponentLocation() + GetForwardVector() *HoldDistance;

	Handle->SetTargetLocationAndRotation(TarhetLocation, GetComponentRotation());

}

void UGrabber::Release(){
	UE_LOG(LogTemp, Warning, TEXT("realese"));
	UPhysicsHandleComponent* Handle = CreateHandle();
	if (Handle->GetGrabbedComponent()!=nullptr){
		Handle->ReleaseComponent();
	}
}

void UGrabber::Grab()
{
    UPhysicsHandleComponent* Handle = CreateHandle();
    if (!Handle) return;

    // Perform trace to find an object
    FHitResult HitResult;
    bool HasHit = PerformTrace(HitResult);
    if (!HasHit) return;

    // Get grabbable component
    UPrimitiveComponent* HitComponent = GetGrabbableComponent(HitResult);
    if (!HitComponent) return;

    TryGrabComponent(Handle, HitComponent, HitResult);
}

bool UGrabber::PerformTrace(FHitResult& HitResult)
{
    FVector Start = GetComponentLocation();
    FVector End = Start + GetForwardVector() * MaxDistance;

    DrawDebugLine(GetWorld(), Start, End, FColor::Red);
    DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

    FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

    return GetWorld()->SweepSingleByChannel(
        HitResult,
        Start, End,
        FQuat::Identity,
        ECC_GameTraceChannel2,
        Sphere
    );
}


UPrimitiveComponent* UGrabber::GetGrabbableComponent(const FHitResult& HitResult)
{
    UPrimitiveComponent* HitComponent = HitResult.GetComponent();
    if (!HitComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("No valid component hit."));
        return nullptr;
    }

    HitComponent->WakeAllRigidBodies();
    return HitComponent;
}

void UGrabber::TryGrabComponent(UPhysicsHandleComponent* Handle, UPrimitiveComponent* HitComponent, const FHitResult& HitResult)
{
    if (!Handle || !HitComponent) return;

    Handle->GrabComponentAtLocationWithRotation(
        HitComponent,
        NAME_None,
        HitResult.ImpactPoint,
        GetComponentRotation()
    );
}

UPhysicsHandleComponent* UGrabber::CreateHandle(){
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


void UGrabber::PlaceStatue()
{
    UPhysicsHandleComponent* Handle = CreateHandle();
    if (!Handle) return;

    AActor* HeldStatue = GetHeldObject();
    if (!HeldStatue) return;

    APedestal* NearestPedestal = FindNearbyPedestal();
    if (!NearestPedestal) return;

    if (NearestPedestal->PlaceStatue(HeldStatue))
    {
        Handle->ReleaseComponent(); 
    }
}

AActor* UGrabber::GetHeldObject()
{
    UPhysicsHandleComponent* Handle = CreateHandle();
    if (!Handle) return nullptr;

    UPrimitiveComponent* GrabbedComponent = Handle->GetGrabbedComponent();
    if (!GrabbedComponent) return nullptr;

    return GrabbedComponent->GetOwner(); 
}


APedestal* UGrabber::FindNearbyPedestal()
{
    FVector PlayerLocation = GetOwner()->GetActorLocation(); 
    float SearchRadius = 200.0f;

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APedestal::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        APedestal* Pedestal = Cast<APedestal>(Actor);
        if (Pedestal && FVector::Dist(PlayerLocation, Pedestal->GetActorLocation()) < SearchRadius)
        {
            return Pedestal;
        }
    }

    return nullptr;
}

