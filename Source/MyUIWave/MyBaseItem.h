#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"	// 생성한 아이템 인터페이스
#include "MyBaseItem.generated.h"

UCLASS()
class MYUIWAVE_API AMyBaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	AMyBaseItem();

protected:
	virtual void OnItemOverlap(AActor* OverlapActor) override;
	virtual void OnItemEndOverlap(AActor* OverlapActor) override;
	virtual void ActivateItem(AActor* Activator) override;
	virtual FName GetItemType() const override;

	virtual void DestoryItem();

	// Category = 'Item' 이런식으로 실수하지 말것
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType;	// GetItemType()을 통해 가져온 아이템 타입을 저장할 변수
};
