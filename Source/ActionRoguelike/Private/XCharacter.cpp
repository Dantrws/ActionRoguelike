// Fill out your copyright notice in the Description page of Project Settings.


#include "XCharacter.h"
#include "Camera\CameraComponent.h"
#include "GameFramework\SpringArmComponent.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "XMagicProjectile.h"
#include "XExplosiveBarrel.h"
#include "Components\CapsuleComponent.h"
#include "XInteractiveComponent.h"
#include "Animation\AnimMontage.h"

// Sets default values
AXCharacter::AXCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmCom = CreateDefaultSubobject<USpringArmComponent>("SpringArmCom");
	SpringArmCom->bUsePawnControlRotation = true;
	SpringArmCom->SetupAttachment(RootComponent);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AXCharacter::OnBeginOverlap );
	

	CameraCom = CreateDefaultSubobject<UCameraComponent>("CameraCom");
	CameraCom->SetupAttachment(SpringArmCom);

	MyMovementComponent=GetCharacterMovement();
	MyMovementComponent->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	MagicProjectileClass = AXMagicProjectile::StaticClass();

	InteractiveComp = CreateDefaultSubobject<UXInteractiveComponent>("InteractComp");
}



void AXCharacter::PrimaryAttack_Implementation()
{
	PlayAnimMontage(AnimMontage);
	if (MagicProjectileClass != nullptr)
	{
		FVector HandLocation = GetMesh()->GetSocketLocation(HandSocket);
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FTransform SpawnTransform = FTransform(GetControlRotation(), HandLocation);
		MagicProjectile = GetWorld()->SpawnActor<AXMagicProjectile>(MagicProjectileClass, SpawnTransform, SpawnParams);
		if (MagicProjectile != nullptr)
		{
			MagicProjectile->Fire();
		}
	}
}

void AXCharacter::PrimaryAttackTemp()
{
	AXCharacter::PrimaryAttack_Implementation();
}

void AXCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;
	AddMovementInput(ControlRot.Vector(), Value);
}

void AXCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;
	//ControlRot.Yaw = ControlRot.Yaw + 90.0f;
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
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

void AXCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AXExplosiveBarrel* ExBarrelTemp = Cast<AXExplosiveBarrel>(OtherActor);
	if (ExBarrelTemp != nullptr)
	{
		ExBarrelTemp->OnHit();
	}
}

void AXCharacter::PrimaryInteract()
{
	InteractiveComp->PrimaryInteract();
}





// Called to bind functionality to input
void AXCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AXCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AXCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AXCharacter::Jump);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AXCharacter::PrimaryAttackTemp);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AXCharacter::PrimaryInteract);
}


