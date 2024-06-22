// Fill out your copyright notice in the Description page of Project Settings.


#include "XItemChest.h"



// Sets default values
AXItemChest::AXItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyMesh");
	RootComponent = BodyMesh;
	BodyMesh->SetCollisionResponseToAllChannels(ECR_Block);
	BodyMesh->SetCollisionObjectType(ECC_WorldDynamic);

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BodyMesh);
	TargetPitch = 100.0f;

}

void AXItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
	UE_LOG(LogTemp, Warning, TEXT("LidMesh"));
}

// Called when the game starts or when spawned
void AXItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

