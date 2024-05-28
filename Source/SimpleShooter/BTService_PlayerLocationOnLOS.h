// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocationOnLOS.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTService_PlayerLocationOnLOS : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	UBTService_PlayerLocationOnLOS();
	protected:
	 void TickNode(UBehaviorTreeComponent &ownerComp, uint8* nodeMemory, float deltaSeconds) override;
};
