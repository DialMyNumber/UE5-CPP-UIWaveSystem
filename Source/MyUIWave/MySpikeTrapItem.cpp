#include "MySpikeTrapItem.h"
#include "Components/BoxComponent.h"

AMySpikeTrapItem::AMySpikeTrapItem()
{
	ItemType = "SpikeTrap";
	DamageAmount = 20;
	SpeedAmount = -10.0f;
	DelayTime = 3.0f;

	UBoxComponent* Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	InitCollision(Box);	// Box Collision 컴포넌트 생성 -> Scene 컴포넌트에 부착, StaticMesh를 Collision에 다시 부착
}

void AMySpikeTrapItem::ActivateItem(AActor* Activator)
{
	// Spike Trap은 사라지지 않고 그 자리에서 반복
}