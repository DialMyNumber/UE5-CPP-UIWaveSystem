#include "MyExplosiveMineItem.h"
#include "Components/SphereComponent.h"

AMyExplosiveMineItem::AMyExplosiveMineItem()
{
	ItemType = "ExplosiveMine";
	DamageAmount = 50;
	SpeedAmount = -50.0f;
	DelayTime = 5.0f;
	ExplosionRadius = 300.0f;

	ActivationCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	InitCollision(ActivationCollision);	
	// Sphere Collision 컴포넌트 생성 -> Scene 컴포넌트에 부착, StaticMesh를 Collision에 다시 부착

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	InitCollision(ExplosionCollision);
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
}

void AMyExplosiveMineItem::ActivateItem(AActor* Activator)
{
	GetWorld()->GetTimerManager().SetTimer(
		ExplosionTimerHandle,	// ExplosionTimerHandle 핸들러를
		this,	// 이 객체에서 가져오고
		&AMyExplosiveMineItem::Explode,	// AMyExplosiveMineItem::Explode 함수를
		DelayTime,	// DelayTime 초 뒤에
		false	// 한 번만 실행 (<-> true : 반복)
	);
}

void AMyExplosiveMineItem::Explode()
{
	TArray<AActor*> OverlappingActors;	// Overlap 되어있는 Actor를 담을 TArray
	ExplosionCollision->GetOverlappingActors(OverlappingActors);	// Overlap 되어있는 Actor를 TArray에 넣기

	for (AActor* Actor : OverlappingActors) // TArray 원소 순회
	{
		if (Actor && Actor->ActorHasTag("Player"))	// Actor가 유효하고, "Player" 태그가 있으면
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("Get %d Damage"), DamageAmount));
		}
	}

	DestroyItem();
}