// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "DrawDebugHelpers.h"
// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(root);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(muzzleFlash, mesh, TEXT("MuzzleFlashSocket"));
	
	FHitResult hit;
	FVector shotDir;
	if(GunTrace(hit, shotDir))
	{
		UGameplayStatics::PlaySoundAtLocation( GetWorld(), muzzleSoundConcrete, hit.Location);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), impactEffect, hit.Location, shotDir.Rotation());
		AActor* hitActor = hit.GetActor();
		if(hitActor != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit actor "));
			FPointDamageEvent DamageEvent(damage, hit, shotDir, nullptr);
			hitActor->TakeDamage(damage, DamageEvent, GetController(), this);
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult &hit, FVector shotDir)
{
	
	AController* ownerController = GetController();
	if(ownerController == nullptr)
		return false;
	FVector location;
	FRotator rotation;
	ownerController->GetPlayerViewPoint(location, rotation);
	FVector end = location + rotation.Vector() * maxRange;
	shotDir = -rotation.Vector();
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(GetOwner());
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(hit, location, end, ECollisionChannel::ECC_GameTraceChannel1, params);
    return bSuccess;
}

AController* AGun::GetController() const
{
	APawn* ownerPawn = Cast<APawn>(GetOwner());
	if(ownerPawn == nullptr)
		return nullptr;
	return ownerPawn->GetController();
}

