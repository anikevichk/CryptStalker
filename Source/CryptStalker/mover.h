// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Pedestal.h"
#include "mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTSTALKER_API Umover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Umover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditAnywhere)
	FVector MoveOffset;

	UPROPERTY(EditAnywhere)
	float MoveTime = 4;

	UPROPERTY(EditAnywhere)
	bool ShouldMove = false;

	FVector OriginalLocation;

	void MoveWall(float DeltaTime);

	APedestal* FindPedestalWithTag(FName Tag);
	TArray<AActor*> FindActorsWithTag(FName Tag);
	void MoveDoor(AActor* Door, float DeltaTime, bool bMoveUp);

	bool bDoorsAreDown = false; 

	void InitializeOriginalLocation();

	FVector TargetLocation;

	UPROPERTY(EditAnywhere)
	FVector MaxHeightOffset; 


	

};
