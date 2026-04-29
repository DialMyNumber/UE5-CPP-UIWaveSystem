#include "MyHealthPackItem.h"

AMyHealthPackItem::AMyHealthPackItem()
{
	// 부모 클래스에서 초기화 하지 않았던 값들은 자식 클래스 생성자에서 초기화
	HPAmount = 30;		// 아이템 획득 시 HP 변화량
	SpeedAmount = 0.0f;	// 아이템 획득 시 이동 속도 변화량
}

void AMyHealthPackItem::ActivateItem(AActor* Activator)
{
	DestroyItem();
}