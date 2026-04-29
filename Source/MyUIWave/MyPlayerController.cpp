#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"

AMyPlayerController::AMyPlayerController()
	: InputMappingContext(nullptr),	// 어차피 블루프린트에서 할당할거긴 하지만 안전하게 nullptr로 초기화
	MoveAction(nullptr),
	JumpAction(nullptr),
	LookAction(nullptr),
	SprintAction(nullptr)
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// LocalPlayer = 현재 플레이어의 객체
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			// LocalPlayer의 UEnhancedInputLocalPlayerSubsystem 을 가져옴,
			// UEnhancedInputLocalPlayerSubsystem는 IMC를 관리하는 서브 시스템
		{
			if (InputMappingContext) // InputMappingContext 가 존재할 때
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
				// AddMappingContext 함수를 통해 0순위로 InputMappingContext 추가
			}
		}
	}
}