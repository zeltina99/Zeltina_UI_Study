// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Title/MyTitleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h" // 레벨 이동(OpenLevel)을 위해 필요
#include "Framework/MyGameInstance.h"// [필수] 비동기 로딩 함수 사용을 위해 추가

void UMyTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 1. 버튼 이벤트 바인딩
	if (ScreenTouchBtn)
	{
		// 버튼이 클릭되면 OnScreenTouched 함수를 실행하도록 연결
		ScreenTouchBtn->OnClicked.AddDynamic(this, &UMyTitleWidget::OnScreenTouched);
	}

	// 2. 깜빡임 애니메이션 재생
	if (BlinkAnim)
	{
		// PlayAnimation(애니메이션, 시작시간, 반복횟수, 재생모드, 재생속도)
		// 반복 횟수(NumLoopsToPlay)가 0이면 무한 반복입니다.
		PlayAnimation(BlinkAnim, 0.0f, 0);
	}
}

void UMyTitleWidget::OnScreenTouched()
{
	/** @brief GameInstance 캐스팅 */
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());

	if (GI)
	{
		/** @brief 비동기 로딩 요청 (기획자가 세팅한 목록 전달) */
		GI->OpenLevelWithAsyncLoad(FName("Lobby"), PreloadAssets);
	}
	else
	{
		/** @brief 예외 처리: GI를 못 찾으면 즉시 이동 */
		UGameplayStatics::OpenLevel(GetWorld(), FName("Lobby"));
	}
}
