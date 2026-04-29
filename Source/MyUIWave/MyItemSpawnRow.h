#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MyItemSpawnRow.generated.h"

// 구조체를 Blueprint에서 변수로 만들 수 있고, 인식할 수 있도록
USTRUCT(BlueprintType)
struct FMyItemSpawnRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	// 비교적 가벼운 FName을 사용하여 메모리 절약

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;
	// 아이템 가져오기, 블루프린트 클래스 or C++ 클래스
	// TSubclassOf : 하드 레퍼런스, 클래스가 항상 메모리에 로드된 상태에서 바로 접근 
	// ( <-> TSoftClassPtr ) : 클래스의 경로만 유지, 필요한 경우에 메모리에 접근하여 로드
	// 권장하는 것은 TSoftClassPtr 이지만 별도의 코드가 추가로 필요하기 때문에 지금 당장은 TSubclassOf 사용

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Spawnchance;	// 각 아이템의 확률
};
