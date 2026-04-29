#include "MyLargeCoinItem.h"
#include "Components/SphereComponent.h"

AMyLargeCoinItem::AMyLargeCoinItem()
{
	// 부모 클래스에서 초기화 하지 않았던 값들은 자식 클래스 생성자에서 초기화
	ItemType = "LargeCoin";
	PointValue = 50;

	USphereComponent* Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	InitCollision(Sphere);	// Box Collision 컴포넌트 생성 -> Scene 컴포넌트에 부착, StaticMesh를 Collision에 다시 부착
}

void AMyLargeCoinItem::ActivateItem(AActor* Activator)
{
	DestroyItem();
}