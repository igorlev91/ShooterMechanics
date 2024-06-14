// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class MOVEMENTEXHIBITION_API UBTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	void IncrementBulletShot(UBehaviorTreeComponent& OwnerComp) const;

protected:
	UPROPERTY(EditAnywhere, Category="Attack")
	FName BlackboardKeyTargetActor = NAME_None;

	UPROPERTY(EditAnywhere, Category="Attack")
	FName BlackboardKeyNumOfBulletShot = NAME_None;
};