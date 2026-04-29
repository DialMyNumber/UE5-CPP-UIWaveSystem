#include "MyLargeCoinItem.h"

AMyLargeCoinItem::AMyLargeCoinItem()
{
	// 부모 클래스에서 초기화 하지 않았던 값들은 자식 클래스 생성자에서 초기화
	PointValue = 50;
	ItemType = "LargeCoin";
}

void AMyLargeCoinItem::ActivateItem(AActor* Activator)
{
	DestroyItem();
}