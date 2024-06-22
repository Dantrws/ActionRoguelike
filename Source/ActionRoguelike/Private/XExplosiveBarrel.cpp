// Fill out your copyright notice in the Description page of Project Settings.


#include "XExplosiveBarrel.h"
#include "Components\SphereComponent.h"
#include "Components\StaticMeshComponent.h"
#include "Particles\ParticleSystemComponent.h"
#include "PhysicsEngine\RadialForceComponent.h"


// Sets default values
AXExplosiveBarrel::AXExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetSphereRadius(100.0f);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RootComponent = SphereComp;
	SetActorEnableCollision(true);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(SphereComp);

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->SetupAttachment(SphereComp);	
	RadialForce->Radius = 500.0f;
}



void AXExplosiveBarrel::OnHit()
{
	RadialForce->FireImpulse();
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
	EffectComp->Activate(true);
}

void AXExplosiveBarrel::ProjectileInteract_Implementation(APawn* InstigatorPawn)
{
	AXExplosiveBarrel::OnHit();
	UE_LOG(LogTemp, Warning, TEXT("worked"));
}

// Called when the game starts or when spawned
void AXExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// onBeginOverlap call on hit?

// Called every frame
void AXExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


