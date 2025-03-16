// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Pedestal.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTSTALKER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Release();

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void PlaceStatue();

	UFUNCTION(BlueprintCallable)
	void TakeStatue();  

	UFUNCTION(BlueprintCallable)
	void HandlePlaceOrTake();
	
	UFUNCTION(BlueprintCallable)
	UPhysicsHandleComponent* CreateHandle();
private:

	UPROPERTY(EditAnywhere)
	float MaxDistance = 400;

	UPROPERTY(EditAnywhere)
	float GrabRadius = 200;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;

	bool PerformTrace(FHitResult& HitResult);
    UPrimitiveComponent* GetGrabbableComponent(const FHitResult& HitResult);
	void TryGrabComponent(UPhysicsHandleComponent* Handle, UPrimitiveComponent* HitComponent, const FHitResult& HitResult);

	APedestal* FindNearbyPedestal();

	UFUNCTION(BlueprintCallable)
	AActor* GetHeldObject();



};
