// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SimpleShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASimpleShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	protected:
		virtual void BeginPlay() override;
	private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> looseScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> winScreenClass;
	UPROPERTY(EditAnywhere)
	float restartDelay = 5.f;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;
	FTimerHandle restartTimer;
	UPROPERTY()
	UUserWidget* hud;
};
