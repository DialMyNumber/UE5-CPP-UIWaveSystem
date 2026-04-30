#include "MyCoinItem.h"
#include "Engine/World.h" // 게임 World를 가져오기
#include "MyGameStateBase.h"

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
		if (UWorld* World = GetWorld())
		{
			if (AMyGameStateBase* GameState = World->GetGameState<AMyGameStateBase>())
			{
				GameState->AddScore(PointValue);
			}
		}

		DestroyItem();
	}
}
