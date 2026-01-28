// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Stage/StagePopupWidget.h"
#include "Framework/MyGameInstance.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UStagePopupWidget::UpdatePopupInfo(const FStageData& Data)
{
	if (TitleText)
	{
		TitleText->SetText(Data.StageName);
	}
	if (DescText)
	{
		DescText->SetText(Data.Description);
	}

	//입장할 레벨 이름 캐싱
	CurrentLevelName = Data.LevelToLoad;

	// TODO: PreviewImage에 Data.Thumnail 비동기 로딩 적용 필요
	// SetBrushFromSoftTexture 등을 활용하여 UI 블로킹 방지
}

void UStagePopupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 입장 버튼
	if (EnterBtn)
	{
		EnterBtn->OnClicked.AddDynamic(this, &UStagePopupWidget::OnEnterClicked);
	}
	// 닫기 버튼
	if (CloseBtn)
	{
		CloseBtn->OnClicked.AddDynamic(this, &UStagePopupWidget::OnCloseClicked);
	}
}

void UStagePopupWidget::OnEnterClicked()
{
	// GameInstance를 통해 비동기 에셋 로딩 및 레벨 이동 요청
	if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance()))
	{
		// 빈 배열을 넘기거나, 로딩이 필요한 추가 에셋 리스트를 넘김
		TArray<TSoftObjectPtr<UObject>> AssetsToLoad;
		GI->OpenLevelWithAsyncLoad(CurrentLevelName, AssetsToLoad);
	}
}

void UStagePopupWidget::OnCloseClicked()
{
	// 팝업 닫기 (Viewport에서 제거)
	RemoveFromParent();
}
