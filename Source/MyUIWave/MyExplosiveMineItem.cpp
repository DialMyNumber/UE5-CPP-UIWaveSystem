#include "MyExplosiveMineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"			// ApplyDamage에 필요

AMyExplosiveMineItem::AMyExplosiveMineItem()
{
	ItemType = "ExplosiveMine";
	DamageAmount = 30;
	SpeedAmount = -300.0f;
	DelayTime = 5.0f;
	ExplosionRadius = 400.0f;

	ActivationCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	InitCollision(ActivationCollision);	
	// Sphere Collision 컴포넌트 생성 -> Scene 컴포넌트에 부착, StaticMesh를 Collision에 다시 부착

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	InitCollision(ExplosionCollision);
	ExplosionCollision->InitSphereRadius(ExplosionRadius);

	bIsActivated = false;
}

void AMyExplosiveMineItem::ActivateItem(AActor* Activator)
{
	if (bIsActivated) return;	// 이미 활성화가 되어있으면 아무것도 하지 않기

	GetWorld()->GetTimerManager().SetTimer(
		ExplosionTimerHandle,	// ExplosionTimerHandle 핸들러를
		this,	// 이 객체에서 가져오고
		&AMyExplosiveMineItem::Explode,	// AMyExplosiveMineItem::Explode 함수를
		DelayTime,	// DelayTime 초 뒤에
		false	// 한 번만 실행 (<-> true : 반복)
	);

	bIsActivated = true;	// 활성화
}

void AMyExplosiveMineItem::Explode()
{
	TArray<AActor*> OverlappingActors;	// Overlap 되어있는 Actor를 담을 TArray
	ExplosionCollision->GetOverlappingActors(OverlappingActors);	// Overlap 되어있는 Actor를 TArray에 넣기

	for (AActor* Actor : OverlappingActors) // TArray 원소 순회
	{
		if (Actor && Actor->ActorHasTag("Player"))	// Actor가 유효하고, "Player" 태그가 있으면
		{
			UGameplayStatics::ApplyDamage(
				Actor,	// 데미지를 받을 AActor
				DamageAmount,
				nullptr, // 데미지를 입히는 원인 주체 ( ex. 지뢰를 심은 Actor )
				this,	// 실제로 데미지를 입히는 AActor
				UDamageType::StaticClass()	// 데미지 타입?
			);
		}
	}

	DestroyItem();
}