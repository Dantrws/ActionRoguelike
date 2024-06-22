// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XGameplayInterface.h"
#include "XItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AXItemChest : public AActor, public IXGameplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn);

public:	
	// Sets default values for this actor's properties
	AXItemChest();
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* LidMesh;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere)
		float TargetPitch;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
