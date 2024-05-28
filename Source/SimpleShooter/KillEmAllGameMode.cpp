// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"
void AKillEmAllGameMode::PawnKilled(APawn *pawnKilled)
{
    Super::PawnKilled(pawnKilled);
    UE_LOG(LogTemp, Warning, TEXT("A pawn killed"));
    APlayerController* playerController = Cast<APlayerController>(pawnKilled->GetController());
    if(playerController != nullptr)
    {
        EndGame(false);
    }
    for(AShooterAIController* controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!controller->IsDead())
        {
            return;
        }
    }
    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool isPlayerWin)
{
   for(AController* controller : TActorRange<AController>(GetWorld()))
   {
        bool isWinner = controller->IsPlayerController() == isPlayerWin;
        controller->GameHasEnded(nullptr, isWinner);
   }
}
