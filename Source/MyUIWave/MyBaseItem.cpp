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
	return ItemType;
}