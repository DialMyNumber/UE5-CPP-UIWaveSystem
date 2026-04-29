#include "MyCoinItem.h"

AMyCoinItem::AMyCoinItem()
{
	// 굳이 초기화 할 필요 x
	ItemType = "DefaultCoin";
	PointValue = 0;
}

void AMyCoinItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("Get %d Points!"), PointValue));
		Destroy();
	}
}
