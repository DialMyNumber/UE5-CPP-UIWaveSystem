#include "MySpikeTrapItem.h"

AMySpikeTrapItem::AMySpikeTrapItem()
{
	ItemType = "SpikeTrap";
	DamageAmount = 20;
	SpeedAmount = -10.0f;
	DelayTime = 3.0f;
}

void AMySpikeTrapItem::ActivateItem(AActor* Activator)
{
	// Spike Trap은 사라지지 않고 그 자리에서 반복
}