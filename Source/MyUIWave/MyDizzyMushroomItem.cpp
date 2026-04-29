#include "MyDizzyMushroomItem.h"
#include "Components/SphereComponent.h"

AMyDizzyMushroomItem::AMyDizzyMushroomItem()
{
	// 부모 클래스에서 초기화 하지 않았던 값들은 자식 클래스 생성자에서 초기화
	ItemType = "DizzyMushroom";
	HPAmount = 10;			// 아이템 획득 시 HP 변화량
	SpeedAmount = -10.0f;	// 아이템 획득 시 이동 속도 변화량

	USphereComponent* Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	InitCollision(Sphere);	// Box Collision 컴포넌트 생성 -> Scene 컴포넌트에 부착, StaticMesh를 Collision에 다시 부착
}

void AMyDizzyMushroomItem::ActivateItem(AActor* Activator)
{
	DestroyItem();
}