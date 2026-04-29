#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"	// 생성한 아이템 인터페이스
#include "MyBaseItem.generated.h"

class UShapeComponent;

UCLASS()
class MYUIWAVE_API AMyBaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	AMyBaseItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UShapeComponent* Collision;	// 콜리전 담당, 모양은 아직 미지정 상태 -> 자식 클래스 생성자에서

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UStaticMeshComponent* StaticMesh;

	// Category = 'Item' 이런식으로 실수하지 말것
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType;	// GetItemType()을 통해 가져온 아이템 타입을 저장할 변수

	virtual void OnItemOverlap(UPrimitiveComponent* OverlappedComp,	// Collision 컴포넌트 자기 자신 
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
		) override;

	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

	virtual void ActivateItem(AActor* Activator) override;

	virtual FName GetItemType() const override;

	void InitCollision(UShapeComponent* InCollision);

	virtual void DestroyItem();
};