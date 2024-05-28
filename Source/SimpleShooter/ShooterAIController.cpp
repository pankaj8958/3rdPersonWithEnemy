// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"
void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    if(AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float deltaTime)
{   
    Super::Tick(deltaTime);
}
bool AShooterAIController::IsDead() const
{
    AShooterCharacter* shooterCharacter = Cast<AShooterCharacter>(GetPawn());
    if(shooterCharacter != nullptr)
    {
        return shooterCharacter->IsDead();
    }
    return true;
}