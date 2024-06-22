// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "XCharacter.generated.h"

class AXInteractiveComponent;

UCLASS()
class ACTIONROGUELIKE_API AXCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AXCharacter();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCharacterMovementComponent* MyMovementComponent;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PrimaryAttack();

	void PrimaryAttackTemp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AXMagicProjectile> MagicProjectileClass;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class AXMagicProjectile* MagicProjectile;

	class UXInteractiveComponent* InteractiveComp;


protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class USpringArmComponent* SpringArmCom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* CameraCom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName HandSocket;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AnimMontage;

	void MoveForward(float Value);
	void MoveRight(float Value);

	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PrimaryInteract();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Tracking)
	void IsActorInJunction( AActor* MyActor, bool& Result);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Tracking)
	void IsActorInJunction02();

};
