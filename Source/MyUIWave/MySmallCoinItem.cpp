#include "MySmallCoinItem.h"
#include "Components/SphereComponent.h"

AMySmallCoinItem::AMySmallCoinItem()
{
	// 부모 클래스에서 초기화 하지 않았던 값들은 자식 클래스 생성자에서 초기화
	ItemType = "SmallCoin";
	PointValue = 10;

	USphereComponent* Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	InitCollision(Sphere);
	// Sphere Collision 컴포넌트 생성 -> Scene 컴포넌트에 부착, StaticMesh를 Collision에 다시 부착
}

void AMySmallCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	// 부모 클래스(MyCoinItem)의 ActivateItem 기능 정도만으로도 충분
	// MySmallCoinItem 만의 기능을 추가하고 싶으면 아래 코드에 추가
}