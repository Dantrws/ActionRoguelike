// Fill out your copyright notice in the Description page of Project Settings.


#include "XInteractiveComponent.h"
#include "XGameplayInterface.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UXInteractiveComponent::UXInteractiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called when the game starts
void UXInteractiveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UXInteractiveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UXInteractiveComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector Start;
	FRotator EyeRotation;
	
	GetOwner()->GetActorEyesViewPoint(Start, EyeRotation);
	FVector End = Start + (EyeRotation.Vector() * 500);

	
	// bool bIsHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);

	TArray<FHitResult> Hits;
	float Radius = 30.0f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	bool bIsHit = GetWorld()->SweepMultiByObjectType(Hits, Start, End, FQuat::Identity, ObjectQueryParams, Shape);
	
	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			if (HitActor->Implements<UXGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(GetOwner());
				IXGameplayInterface::Execute_Interact(HitActor, MyPawn);
				UE_LOG(LogTemp, Warning, TEXT("Hello"));
				DrawDebugSphere(GetWorld(), Hit.Location, Radius, 30, FColor::Green, false, 2.0f, 0, 1.0f);
				break;
			}
			
		}
	}
	

	FColor DebugColor = bIsHit ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), Start, End, DebugColor,false, 2.0f, 0, 2.0f);
}
