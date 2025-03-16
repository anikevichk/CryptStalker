// Fill out your copyright notice in the Description page of Project Settings.


#include "Pedestal.h"
#include "Grabber.h"
#include "TriggerComponent.h"
#include "Kismet/GameplayStatics.h"
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

    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors);
    for (AActor* Actor : OverlappingActors)
    {
        if (Actor->ActorHasTag("gold_man")) 
        {
            PlacedStatue = Actor;
            PlacedStatue->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
            
            UPrimitiveComponent* StatueMesh = Cast<UPrimitiveComponent>(PlacedStatue->GetRootComponent());
            if (StatueMesh)
            {
                StatueMesh->SetSimulatePhysics(false);
            }

            break;
        }}
	
}

// Called every frame
void APedestal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APedestal::PlaceStatue(AActor* Statue)
{
    if (!Statue)
    {
        return false;
    }

    if (IsOccupied())
    {
        return false;
    }


    PlacedStatue = Statue;

    FVector PedestalTop;
    bool GoldMan = Statue->ActorHasTag("gold_man");
    bool Replacemant = Statue->ActorHasTag("replacemant");

    PedestalTop = GetActorLocation() + FVector(0, 0, 100);

    FRotator CorrectRotation = GetActorRotation(); 
    Statue->SetActorLocationAndRotation(PedestalTop, CorrectRotation);

    Statue->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

    UPrimitiveComponent* StatueMesh = Cast<UPrimitiveComponent>(Statue->GetRootComponent());
    if (StatueMesh)
    {
        StatueMesh->SetSimulatePhysics(false);
    }

    return true;
}

int APedestal::GetOccupiedPedestals(UWorld* World)
{
    int OccupiedPedestals = 0;
    TArray<AActor*> Pedestals;

    UGameplayStatics::GetAllActorsOfClass(World, APedestal::StaticClass(), Pedestals);

    for (AActor* Actor : Pedestals)
    {
        APedestal* Pedestal = Cast<APedestal>(Actor);
        if (Pedestal && Pedestal->IsOccupied()) 
        {
            OccupiedPedestals++;
        }
    }

    return OccupiedPedestals;
}

