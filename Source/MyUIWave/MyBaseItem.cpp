#include "MyBaseItem.h"
#include "Components/ShapeComponent.h"

AMyBaseItem::AMyBaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	// 여기서 Collision 생성하지 않음 -> 
	// InitCollision() 함수 매개변수를 통해 다양한 모양의 Collision 을 자식 클래스 생성자에서 생성 예정

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Scene); // Collision이 나중에 붙을 거지만 일단 Scene에 붙임
}

void AMyBaseItem::OnItemOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// OtherActor가 nullptr이 아니고, OtherActor가 "Player" 라는 태그인지 확인
	if (OtherActor && OtherActor->ActorHasTag("Player")) 
	{
		ActivateItem(OtherActor);
	}
}

void AMyBaseItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
}

void AMyBaseItem::ActivateItem(AActor* Activator)
{
}

FName AMyBaseItem::GetItemType() const
{
	return ItemType;	// 초기화는 가장 마지막 자식 클래스에서
}

void AMyBaseItem::DestroyItem()
{
	Destroy();	// 아이템을 먹었으면 소멸
}

void AMyBaseItem::InitCollision(UShapeComponent* InCollision)
{
	if (!InCollision)	// nullptr 방지
	{
		return;
	}

	Collision = InCollision;
	Collision->SetupAttachment(Scene);

	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	// Collision Preset의 Default를 OverlapAllDynamic(동적으로 움직이는 액터만 Overlap)

	// BeginOverlap, EndOverlap이 실행될 때 어떤 함수를 실행할지 바인딩
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AMyBaseItem::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AMyBaseItem::OnItemEndOverlap);
	// 게임 실행 전 : 어떤 액터가 어떤 오브젝트에 부딪힐지 전혀 알 수 없음
	// 런타임으로 이루어져야함 -> AddDynamic 이라는 기능을 통해 동적으로 바인딩

	StaticMesh->SetupAttachment(Collision); // StaticMesh를 Collision 밑으로 재부착(Re-SetupAttachment)
}