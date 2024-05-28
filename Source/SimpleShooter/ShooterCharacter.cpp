// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameMode.h"
// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	health = maxHealth;
	gun = GetWorld()->SpawnActor<AGun>(gunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));
	gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AShooterCharacter::IsDead() const
{
    return health <= 0;
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("fire"), IE_Pressed, this, &AShooterCharacter::Fire);
}
float AShooterCharacter::TakeDamage(float damageAmount, FDamageEvent const &damageEvent, AController *eventInstigator, AActor *damageCauser)
{
	float damageTaken = Super::TakeDamage(damageAmount, damageEvent, eventInstigator, damageCauser);
	damageTaken = FMath::Min(health, damageTaken);
	health -= damageTaken;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f damageTaken %f"), health, damageTaken);
	if(IsDead())
	{
		ASimpleShooterGameMode* gameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameMode>();
		if(gameMode != nullptr)
		{
			gameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return damageTaken;
}
void AShooterCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector()*value);
}
void AShooterCharacter::LookUp(float value)
{
	AddControllerPitchInput(value * rotationRate * GetWorld()->GetDeltaSeconds());
}
void AShooterCharacter::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector()*value);	
}
void AShooterCharacter::LookRight(float value)
{
	AddControllerYawInput(value * rotationRate * GetWorld()->GetDeltaSeconds());
}
void AShooterCharacter::Fire()
{
	gun->PullTrigger();
}

float AShooterCharacter::GethealthPercent() const
{
    return health/maxHealth;
}
