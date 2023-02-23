// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BlasterHUD.generated.h"

USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY()//so the reflection system can work with FHUDPackage struct
public:
	UPROPERTY() // ADDED THIS!!!
	UTexture2D* CrosshairsCenter;
	UPROPERTY() // ADDED THIS!!!
	UTexture2D* CrosshairsLeft;
	UPROPERTY() // ADDED THIS!!!
	UTexture2D* CrosshairsRight;
	UPROPERTY() // ADDED THIS!!!
	UTexture2D* CrosshairsTop;
	UPROPERTY() // ADDED THIS!!!
	UTexture2D* CrosshairsBottom;
	float CrosshairSpread;
};

UCLASS()
class BLASTER_API ABlasterHUD : public AHUD
{
	GENERATED_BODY()
	virtual void DrawHUD() override;

private:
	FHUDPackage HUDPackage;

	UPROPERTY(EditAnywhere)
	float CrosshairSpreadMax = 16.f;

	void DrawCrossHair(UTexture2D* Texture, FVector2D ViewportCenter, FVector2D Spread);
public:
	FORCEINLINE void SetHUDPackage(const FHUDPackage& Package) { HUDPackage = Package; }//setter
};
