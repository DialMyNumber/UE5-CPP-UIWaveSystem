#include "MyOverlapConsumableItem.h"
#include "Math/UnrealMathUtility.h"
#include "MyCPPCharacter.h"				// 적용시킬 Actor

AMyOverlapConsumableItem::AMyOverlapConsumableItem()
{
}

void AMyOverlapConsumableItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		AMyCPPCharacter* PlayerCharacter = Cast<AMyCPPCharacter>(Activator);
		if (HPAmount != 0) 
		{
			PlayerCharacter->AddCurrentHealth(HPAmount);
		}

		if (!FMath::IsNearlyZero(SpeedAmount) && !FMath::IsNearlyZero(SpeedDuration)) {
			PlayerCharacter->AddNormalSpeed(SpeedAmount, SpeedDuration);
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, 
				FString::Printf(TEXT("Speed Changed : %f for %f seconds!"), SpeedAmount, SpeedDuration));
		}

		DestroyItem();
	}
}