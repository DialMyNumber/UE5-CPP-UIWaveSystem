#include "MyExplosiveMineItem.h"

AMyExplosiveMineItem::AMyExplosiveMineItem()
{
	DamageAmount = 50;
	SpeedAmount = -50.0f;
	DelayTime = 5.0f;
}

void AMyExplosiveMineItem::ActivateItem(AActor* Activator)
{
	Destroy();
}