// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationOnLOS.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
UBTService_PlayerLocationOnLOS::UBTService_PlayerLocationOnLOS()
{
    NodeName = "Update Loaction on LOS";
}

void UBTService_PlayerLocationOnLOS::TickNode(UBehaviorTreeComponent &ownerComp, uint8 *nodeMemory, float deltaSeconds)
{
    Super::TickNode(ownerComp, nodeMemory, deltaSeconds);
     APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(playerPawn == nullptr)
    {
        return;
    }
    if(ownerComp.GetAIOwner() == nullptr)
    {
        return;
    }
    if(ownerComp.GetAIOwner()->LineOfSightTo(playerPawn))
    {
        ownerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), playerPawn);
    } else
    {
        /* code */
        ownerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
    
}
