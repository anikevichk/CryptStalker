// Fill out your copyright notice in the Description page of Project Settings.


#include "Pedestal.h"
#include "TriggerComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APedestal::APedestal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PedestalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PedestalMesh"));
    RootComponent = PedestalMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/MedievalDungeon/Meshes/Props/SM_Gargoyle_Statue_Stand.SM_Gargoyle_Statue_Stand"));
    if (MeshAsset.Succeeded())
    {
        PedestalMesh->SetStaticMesh(MeshAsset.Object);
    }


    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/MedievalDungeon/Materials/M_Gargoyle_Stand_Inst.M_Gargoyle_Stand_Inst"));
    if (MaterialAsset.Succeeded())
    {
        PedestalMesh->SetMaterial(0, MaterialAsset.Object);
    }

    TriggerZone = CreateDefaultSubobject<UTriggerComponent>(TEXT("TriggerZone"));
	TriggerZone->SetupAttachment(PedestalMesh);
    TriggerZone->SetWorldScale3D(FVector(1, 1, 3.5));

}

// Called when the game starts or when spawned
void APedestal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APedestal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APedestal::PlaceStatue(AActor* Statue){
    if (IsOccupied()){
        return false;
    }
    PlacedStatue = Statue;
    Statue->SetActorLocation(GetActorLocation()); 
    Statue->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform); 

    UE_LOG(LogTemp, Log, TEXT("Статуя установлена на колонну!"));
    return true;
}
