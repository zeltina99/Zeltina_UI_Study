// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Result/ResultPopupWidget.h"
#include "Components/Button.h"
#include "Framework/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UResultPopupWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// ★ 이벤트 중복 방지의 핵심: NativeConstruct가 아닌 NativeOnInitialized에서 바인딩!
	if (ReturnToStageBtn)
	{
		ReturnToStageBtn->OnClicked.AddDynamic(this, &UResultPopupWidget::OnReturnClicked);
	}
}

void UResultPopupWidget::OnReturnClicked()
{
	// 1. 버튼을 비활성화해서 '따닥(Double Click)'으로 인한 중복 실행 방지
	if (ReturnToStageBtn)
	{
		ReturnToStageBtn->SetIsEnabled(false);
	}

	// 2. GameInstance에 접근하여 "나 1-1 깼어!"라고 보고
	if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance()))
	{
		// [수정] 무조건 1단계 클리어 처리 (테스트용)
		GI->UpdateClearProgress(1);

		// ★ [추가] "로비 도착하면 바로 스테이지 맵(StageMap) 띄워줘!" 라고 메모
		GI->NextLobbyScreen = FName("StageMap");

		// 그 다음 이동
		GI->OpenLevelWithAsyncLoad(FName("Lobby"), {});
	}
}
