// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XGameplayInterface.h"
#include "XExplosiveBarrel.generated.h"


UCLASS()
class ACTIONROGUELIKE_API AXExplosiveBarrel : public AActor , public IXGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXExplosiveBarrel();
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
		class URadialForceComponent* RadialForce;

	UPROPERTY(EditAnywhere)
		class USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* EffectComp;

	UFUNCTION(BlueprintCallable)
		void OnHit();

	
	void ProjectileInteract_Implementation(APawn* InstigatorPawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
