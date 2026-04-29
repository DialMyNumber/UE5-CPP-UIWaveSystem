#pragma once

#include "CoreMinimal.h"
#include "MyOverlapTrapItem.h"
#include "MySpikeTrapItem.generated.h"

UCLASS()
class MYUIWAVE_API AMySpikeTrapItem : public AMyOverlapTrapItem
{
	GENERATED_BODY()

public:
	AMySpikeTrapItem();

	virtual void ActivateItem(AActor* Activator) override;
	
};
