#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBaseItem.generated.h"

UCLASS()
class MYUIWAVE_API AMyBaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyBaseItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
