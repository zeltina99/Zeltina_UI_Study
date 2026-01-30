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
		// [TODO] 실제로는 이 팝업을 띄울 때 "몇 스테이지를 깼는지" 데이터를 받아와야 합니다.
		// 지금은 테스트를 위해 무조건 "1단계(Index 1) 클리어"로 갱신합니다.
		const int32 ClearedStageIndex = 1;
		GI->UpdateClearProgress(ClearedStageIndex);

		// 3. 로비(WBP_StageMap이 있는 레벨)로 비동기 로딩 이동
		// "Lobby"는 실제 레벨 파일 이름과 일치해야 합니다.
		GI->OpenLevelWithAsyncLoad(FName("Lobby"), {});
	}
}
