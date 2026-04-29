#pragma once

#include "CoreMinimal.h"
#include "MyCoinItem.h"
#include "MySmallCoinItem.generated.h"

UCLASS()
class MYUIWAVE_API AMySmallCoinItem : public AMyCoinItem
{
	GENERATED_BODY()

public:
	AMySmallCoinItem();

	virtual void ActivateItem(AActor* Activator) override;
	
};
