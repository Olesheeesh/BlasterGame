#pragma once

UENUM(BlueprintType)
enum class ETurningInPlace : uint8
{
	ETIP_Left UMETA(DislayName = "TurningLeft"),
	ETIP_Right UMETA(DislayName = "TurningRight"),
	ETIP_NotTurning UMETA(DislayName = "NotTurning"),
	ETIP_MAX UMETA(DislayName = "DefaultMAX")
};
