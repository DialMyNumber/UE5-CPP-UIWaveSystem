// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

// 리플렉션 시스템에 등록하기 위한 코드, 실제 구현은 다른 클래스에서
UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

//--------------------------- 실제 동작하는 부분, 이쪽에 실제 구현을 하면 됨
// 구현할 아이템 목록
// 인터페이스 특성상 확장성과 재사용성을 고려하여 구현
// 구현 예정 - 지뢰, 스파이크 트랩, 힐링팩, 점수코인, 환각 버섯, 깃털
// 힐링팩, 점수코인	- 오버랩 | 즉시 발동	
// 환각 버섯			- 오버랩 | 즉시 발동	| 일정 시간 동안 WASD 컨트롤 반전, 색수차 포스트 프로세싱
// 깃털				- 오버랩 | 즉시 발동	| 일정 시간 동안 이동 속도 증가
// 스파이크 트랩		- 오버랩 | 즉시 발동 -> 카운트 시작 -> N초뒤 스파이크가 솟아오름		| 데미지
// 지뢰				- 오버랩 | 즉시 발동 -> 카운트 시작 -> N초뒤 폭발					| 데미지


// MyBaseItem(부모 클래스) | Actor 클래스
// ├── MyCoinItem	| 오버랩
// │   ├── SmallCoin
// │   └── BigCoin
// ├── TrapItem	| 오버랩
// │   ├── Mine
// │   └── SpikeTrap
// └── OverlapConsumableItem (소모 / 버프 아이템) | 오버랩
//		├── BuffItem (버프)
//		│   ├── JumpBoostFeather
//		│   └── Healing Pack
//		└── DebuffItem (디버프)
//			└── HallucinogenicMushroom (일정 시간 동안 WASD 컨트롤 반전, 색수차 포스트 프로세싱)

class MYUIWAVE_API IItemInterface
{
	GENERATED_BODY()

public:
	virtual void OnItemOverlap(AActor* OverlapActor) = 0;
	// 순수 가상 함수로 선언 : 이 인터페이스를 상속하는 자식 클래스는 반드시 오버라이딩으로 구현해야함
	// Character가 아닌 Actor인 이유 : AI가 조종하는 Pawn이나 Monster 등 Character 외에도 발동할 수 있도록
	// ㄴ> 그때그때 Cast를 통해 캐스팅만 하면 간단하게 적용 가능

	virtual void OnItemEndOverlap(AActor* OverlapActor) = 0;
	virtual void ActivateItem(AActor* Activator) = 0;
	virtual FName GetItemType() const = 0;
	// Type 등을 알아낼 때는 (FString보다) FName이 속도가 빠르고 메모리도 절약 가능
	// const : 읽기 전용으로 사용할 목적
};