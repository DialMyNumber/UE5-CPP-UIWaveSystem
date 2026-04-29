#pragma once

#include "CoreMinimal.h"
#include "MyCoinItem.h"
#include "MyLargeCoinItem.generated.h"

UCLASS()
class MYUIWAVE_API AMyLargeCoinItem : public AMyCoinItem
{
	GENERATED_BODY()

public:
	AMyLargeCoinItem();

	virtual void ActivateItem(AActor* Activator) override;
	
};
