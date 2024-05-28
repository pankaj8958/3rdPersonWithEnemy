// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gun.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float damageAmount, struct FDamageEvent const &damageEvent, class AController* eventInstigator, AActor* damageCauser) override;
	void Fire();
	UFUNCTION(BlueprintPure)
	float GethealthPercent() const;
private:
	void MoveForward(float value);
	void LookUp(float value);
	void MoveRight(float value);
	void LookRight(float value);

	UPROPERTY(EditAnywhere)
	float rotationRate = 10;
	UPROPERTY(EditDefaultsOnly)
	float maxHealth = 100;
	UPROPERTY(VisibleAnywhere)
	float health;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> gunClass;
	UPROPERTY()
	AGun* gun;
};
