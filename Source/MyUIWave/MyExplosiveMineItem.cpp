#include "MyExplosiveMineItem.h"
#include "Components/SphereComponent.h"

AMyExplosiveMineItem::AMyExplosiveMineItem()
{
	ItemType = "ExplosiveMine";
	DamageAmount = 50;
	SpeedAmount = -50.0f;
	DelayTime = 5.0f;
	ExplosionRadius = 300.0f;

	USphereComponent* Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	InitCollision(Sphere);	// Box Collision 컴포넌트 생성 -> Scene 컴포넌트에 부착, StaticMesh를 Collision에 다시 부착
}

void AMyExplosiveMineItem::ActivateItem(AActor* Activator)
{
	Destroy();
}