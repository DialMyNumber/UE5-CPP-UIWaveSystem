#include "MyBaseItem.h"

AMyBaseItem::AMyBaseItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMyBaseItem::OnItemOverlap(AActor* OverlapActor)
{
}

void AMyBaseItem::OnItemEndOverlap(AActor* OverlapActor)
{
}

void AMyBaseItem::ActivateItem(AActor* Activator)
{
}

FName AMyBaseItem::GetItemType() const
{
	return ItemType;	// 초기화는 가장 마지막 자식 클래스에서
}

void AMyBaseItem::DestoryItem()
{
	Destroy();	// 아이템을 먹었으면 소멸
}