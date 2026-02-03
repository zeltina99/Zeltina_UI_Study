// Source/UI_Test/Private/UI/InGame/InGameHUDWidget.cpp

#include "UI/InGame/InGameHUDWidget.h"
#include "UI/InGame/SkillSlotWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Controller/LobbyPlayerController.h" // 필요 시 인게임 컨트롤러로 변경

#pragma region 초기화

void UInGameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 일시정지 버튼 바인딩
	if (PauseBtn)
	{
		PauseBtn->OnClicked.AddDynamic(this, &UInGameHUDWidget::OnPauseClicked);
	}

	// 초기화 (예시 데이터)
	UpdateHealth(100.0f, 100.0f);
}

#pragma endregion 초기화

#pragma region 상태 업데이트

void UInGameHUDWidget::UpdateHealth(float CurrentHP, float MaxHP)
{
	if (MaxHP <= 0.0f) return;

	float Percent = FMath::Clamp(CurrentHP / MaxHP, 0.0f, 1.0f);

	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}

	if (HealthText)
	{
		// "100 / 100" 형식으로 텍스트 갱신
		FText StatusMsg = FText::Format(FText::FromString(TEXT("{0} / {1}")),
			FText::AsNumber((int32)CurrentHP),
			FText::AsNumber((int32)MaxHP));
		HealthText->SetText(StatusMsg);
	}
}

void UInGameHUDWidget::SetStageName(FText StageName)
{
	if (StageNameText)
	{
		StageNameText->SetText(StageName);
	}
}

#pragma endregion 상태 업데이트

#pragma region 이벤트 핸들러

void UInGameHUDWidget::OnPauseClicked()
{
	// 일시정지 팝업 요청 로직
	// 예: Controller->ShowPausePopup();
	UE_LOG(LogTemp, Log, TEXT("⏸️ [InGameHUD] Pause Requested."));
}

#pragma endregion 이벤트 핸들러