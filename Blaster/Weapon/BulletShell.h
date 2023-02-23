// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletShell.generated.h"

UCLASS()
class BLASTER_API ABulletShell : public AActor
{
	GENERATED_BODY()

public:
	ABulletShell();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);//collision box, actor being hit, comp that was hit, Impuls

private:
	UPROPERTY(VisibleAnyWhere, Category = "Projectile Properties")
	UStaticMeshComponent* ShellMesh;

	UPROPERTY(EditAnywhere)
	float MinShellEjectionImpulse;

	UPROPERTY(EditAnywhere)
	float MaxShellEjectionImpulse;

	UPROPERTY(EditAnywhere)
	class USoundCue* ShellSound;

	UPROPERTY(EditAnywhere)
	float ShellLifeTime;

	bool bHitGround = false;
};
