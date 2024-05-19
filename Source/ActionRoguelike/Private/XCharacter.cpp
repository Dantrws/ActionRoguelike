// Fill out your copyright notice in the Description page of Project Settings.


#include "XCharacter.h"
#include "Camera\CameraComponent.h"
#include "GameFramework\SpringArmComponent.h"

// Sets default values
AXCharacter::AXCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmCom = CreateDefaultSubobject<USpringArmComponent>("SpringArmCom");
	SpringArmCom->SetupAttachment(RootComponent);

	CameraCom = CreateDefaultSubobject<UCameraComponent>("CameraCom");
	CameraCom->SetupAttachment(SpringArmCom);


}

void AXCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value, false);
}


// Called when the game starts or when spawned
void AXCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AXCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AXCharacter::MoveForward);
	PlayerInputComponent->BindAxis("LookAround", this, &APawn::AddControllerYawInput);
}

