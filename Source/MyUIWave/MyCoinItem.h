#pragma once

#include "CoreMinimal.h"
#include "MyBaseItem.h"
#include "MyCoinItem.generated.h"

UCLASS()
class MYUIWAVE_API AMyCoinItem : public AMyBaseItem
{
	GENERATED_BODY()

public:
	AMyCoinItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Coin")
	int32 PointValue;	// 코인 획득에 따른 게임 점수

	virtual void ActivateItem(AActor* Activator) override;
};