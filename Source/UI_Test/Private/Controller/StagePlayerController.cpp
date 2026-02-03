// Source/UI_Test/Private/Controller/StagePlayerController.cpp

#include "Controller/StagePlayerController.h"
#include "UI/InGame/InGameHUDWidget.h"
#include "EnhancedInputSubsystems.h"

AStagePlayerController::AStagePlayerController()
{
	bShowMouseCursor = false; // 인게임에서는 마우스 숨김 (필요시 true)
}

void AStagePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 1. 입력 매핑 컨텍스트(IMC) 추가
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (auto* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	// 2. 인게임 HUD 생성 및 띄우기
	if (InGameHUDClass)
	{
		InGameHUDInstance = CreateWidget<UInGameHUDWidget>(this, InGameHUDClass);
		if (InGameHUDInstance)
		{
			InGameHUDInstance->AddToViewport();

			// 초기 데이터 설정 (예: 캐릭터 HP 연결 등)
			// InGameHUDInstance->UpdateHealth(CurrentHP, MaxHP);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[StageController] InGameHUDClass is NOT set! Check Blueprint."));
	}
}

void AStagePlayerController::ShowPausePopup()
{
	// TODO: WBP_PausePopup 위젯을 띄우는 로직 구현
	// CommonUI의 PushWidget 등을 사용하거나 CreateWidget 사용
	UE_LOG(LogTemp, Log, TEXT("[StageController] Pause Popup Requested."));

	// 예시: SetPause(true);
}