// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
void ASimpleShooterPlayerController::GameHasEnded(AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    UE_LOG(LogTemp, Warning, TEXT(" Game Has Ended "));
    if(bIsWinner)
    {
        UUserWidget* winScreen = CreateWidget(this, winScreenClass);
        if(winScreen != nullptr)
        {
            winScreen->AddToViewport();
        }
    } else
    {
        UUserWidget* loseScreen = CreateWidget(this, looseScreenClass);
        if(loseScreen != nullptr)
        {
            loseScreen->AddToViewport();
        }
    }
    if(hud != nullptr)
    {
        hud->RemoveFromViewport();
    }
    GetWorldTimerManager().SetTimer(restartTimer, this, &APlayerController::RestartLevel, restartDelay);
}

void ASimpleShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    hud = CreateWidget(this, HUDClass);
    if(hud != nullptr)
    {
        hud->AddToViewport();
    }
}
