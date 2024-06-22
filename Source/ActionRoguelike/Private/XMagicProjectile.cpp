// Fill out your copyright notice in the Description page of Project Settings.


#include "XMagicProjectile.h"
#include "Components\SphereComponent.h"
#include "Particles\ParticleSystemComponent.h"
#include "GameFramework\ProjectileMovementComponent.h"
#include "XGameplayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values
AXMagicProjectile::AXMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	SphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block);
	SphereComp->SetSphereRadius(20);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AXMagicProjectile::OnBeginOverlap);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

void AXMagicProjectile::Fire()
{
	
}

void AXMagicProjectile::Hit()
{

}

void AXMagicProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		if (OtherActor->Implements<UXGameplayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(GetOwner());
			IXGameplayInterface::Execute_ProjectileInteract(OtherActor,MyPawn);
		}
		
		DrawDebugSphere(GetWorld(), SweepResult.Location, 20.0f, 10, FColor::Red,false, 2.0f, 0, 2.0f);
	}
	UE_LOG(LogTemp, Warning, TEXT("worked02"));
}


// Called when the game starts or when spawned
void AXMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

