#include "MyExplosiveMineItem.h"

AMyExplosiveMineItem::AMyExplosiveMineItem()
{
	ItemType = "ExplosiveMine";
	DamageAmount = 50;
	SpeedAmount = -50.0f;
	DelayTime = 5.0f;
}

void AMyExplosiveMineItem::ActivateItem(AActor* Activator)
{
	Destroy();
}