// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletShell.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ABulletShell::ABulletShell()//constructor
{
	PrimaryActorTick.bCanEverTick = false;//чтобы не тикало когда нам это не нужно

	ShellMesh = CreateDefaultSubobject<UStaticMeshComponent>("ShellMesh");
	SetRootComponent(ShellMesh);
	ShellMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	ShellMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	ShellMesh->SetSimulatePhysics(true);
	ShellMesh->SetEnableGravity(true);
	ShellMesh->SetNotifyRigidBodyCollision(false);//simulation generate Hit Events
	ShellLifeTime = 2.f;
}

// Called when the game starts or when spawned
void ABulletShell::BeginPlay()
{
	Super::BeginPlay();
	ShellMesh->OnComponentHit.AddDynamic(this, &ABulletShell::OnHit);
	ShellMesh->AddImpulse(GetActorForwardVector() * FMath::FRandRange(MinShellEjectionImpulse, MaxShellEjectionImpulse));
	SetLifeSpan(ShellLifeTime);
}

void ABulletShell::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
	if(ShellSound && !bHitGround)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation());
		bHitGround = true;
	}
}


