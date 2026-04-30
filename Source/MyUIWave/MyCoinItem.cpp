#include "MyCoinItem.h"
#include "Engine/World.h" // 게임 World를 가져오기
#include "MyGameState.h"

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
			if (AMyGameState* GameState = World->GetGameState<AMyGameState>())
			{
				GameState->AddScore(PointValue);	// 점수 추가
				GameState->OnCoinCollected();	// 코인 개수 카운트 호출
			}
		}

		DestroyItem();
	}
}
