// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	//Revizar distancia entre la AI y el PlayerCharacter

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();

	if(ensure(BlackBoardComp))
	{
		AActor* TargetActor = Cast<AActor>(	BlackBoardComp->GetValueAsObject("TargetActor"));
		if(TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if(ensure(MyController))
			{
				APawn* AIPawn = MyController->GetPawn();
				if(ensure(AIPawn))
				{
					//Is in Distance?
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(),AIPawn->GetActorLocation());
					bool bWithinRange = DistanceTo < 2000.0f;
					//Is visible to the AI?
					bool bHasLOS = false;
					if(bWithinRange)
					{
						bHasLOS = MyController->LineOfSightTo(TargetActor);

					}

					BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName,(bWithinRange && bHasLOS));
				}
			}
		}
	}
	
}
