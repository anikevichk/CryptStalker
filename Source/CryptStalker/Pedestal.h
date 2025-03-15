// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "TriggerComponent.h" 
#include "Pedestal.generated.h"

UCLASS()
class CRYPTSTALKER_API APedestal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APedestal();

	bool IsOccupied() const {return PlacedStatue != nullptr; }

	bool PlaceStatue(AActor* Statue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Pedestal")
    AActor* PlacedStatue = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Pedestal")
	UStaticMeshComponent* PedestalMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Pedestal")
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pedestal")
	UTriggerComponent* TriggerZone;


};
