// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blaster/BlasterTypes/TurningInPlace.h"
#include "BlasterCharacter.generated.h"

UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABlasterCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;// Called to bind functionality to input
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	void PlayFireMontage(bool bAiming);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void EquipButtonPressed();
	void CrouchButtonPressed();
	void AimButtonPressed();
	void AimButtonReleased();
	void SprintButtonPressed();
	void SprintButtonReleased();
	void SetSprint(bool bIsSprinting);
	void AimOffset(float DeltaTime);
	virtual void Jump() override;
	void FireButtonPressed();
	void FireButtonReleased();

	UFUNCTION(Server, Reliable)
	void ServerSetSprint(bool bIsSprinting);

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* OverheadWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	class AWeapon* OverlappingWeapon;

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	UPROPERTY(VisibleAnywhere)
	class UCombatComponent* Combatt;

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	UPROPERTY(Replicated)
	bool isSprinting;

	UPROPERTY(Replicated)
	float BaseSpeed = 550.f;

	UPROPERTY(Replicated)
	float SprintSpeed = 750.f;

	bool isMovingRight;
	float AO_Yaw; //Горизонтальная ось
	float InterpAO_Yaw;
	float AO_Pitch; //Вертикальная ось
	FRotator StartingAimRotation;

	ETurningInPlace TurningInPlace;
	void TurnInPlace(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = Combat)
	class UAnimMontage* FireWeaponMontage;

public:	
	void SetOverlappingWeapon(AWeapon* Weapon);
	bool isWeaponEquipped();
	bool isAiming(); //getter for BlasterCharacter
	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; } //getter AO_Yaw
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; } //getter AO_Pitch
	FORCEINLINE float GetBaseSpeed() const { return BaseSpeed; } //use getter because BaseSpeed is a private variable 
	AWeapon* GetEquippedWeapon();
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; } //returning what enum:: ETurnInPlace equals
	FVector GetHitTarget() const;

	float MaxSpeed;
	void UELogInfo(float Value);
};



//tо replicate:
//	1.Set UPROPERTY(Replicated)
//	2.Go to CombatComponent.cpp and add DOREPLIFETIME to GetLifeTimeReplicatedProps
//	3.create protected: UFUNCTION(Server, Reliable) with Server foo
//  4.Declare with *_implementation
//  Relicated - значит что все клиенты будут значть значение "переменной"