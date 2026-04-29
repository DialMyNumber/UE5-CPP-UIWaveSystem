#include "MyOverlapConsumableItem.h"
#include "Math/UnrealMathUtility.h"

AMyOverlapConsumableItem::AMyOverlapConsumableItem()
{
}

void AMyOverlapConsumableItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (HPAmount != 0) {
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("Get %d HP!"), HPAmount));
		}

		if (!FMath::IsNearlyZero(SpeedAmount)) {
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("Get %f Speed!"), SpeedAmount));
		}

		DestroyItem();
	}
}