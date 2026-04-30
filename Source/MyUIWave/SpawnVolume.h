#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyItemSpawnRow.h"		// 아이템 테이블
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class MYUIWAVE_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")	// 컴포넌트의 일반적인 인자
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;	// 스폰 범위를 지정할 Box Component

	// 객체를 바꿔야하기 때문에 EditAnywhere
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	UDataTable* ItemDataTable;	// 아이템 데이터 테이블

	// UFUNCTION(BlueprintCallable, Category = "Spawning") // 테스트 정도에만 필요
	FVector GetRandomPointInVolume() const;		// Getter라서 const로 읽기 전용
	// 랜덤 FVector를 반환

	// UFUNCTION(BlueprintCallable, Category = "Spawning") // 테스트 정도에만 임시로 사용
	AActor* SpawnItem(TSubclassOf<AActor> ItemClass);	// TSubclassOf : 해당 클래스 포함 하위 클래스만 허용
	// 어떤 액터를 스폰할지 알려줘야하기 때문에 반환값 = AActor

	FMyItemSpawnRow* GetRandomItem() const;
	// 읽기 전용으로 const, 딱히 UFUNCTION() 해주지 않아도 됨

	UFUNCTION(BlueprintCallable, Category = "Spawning")	// 테스트 정도에만 임시로 사용
	AActor* SpawnRandomItem();
	// 어떤 액터를 스폰할지 알려줘야하기 때문에 반환값 = AActor
};