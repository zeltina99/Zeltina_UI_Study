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

	CurrentLevelName = Data.LevelToLoad;

	// [수정] 썸네일 이미지 로딩 로직 추가
	if (PreviewImage)
	{
		// 1. 데이터에 썸네일 경로가 있는지 확인
		if (!Data.Thumbnail.IsNull())
		{
			// 2. 동기 로딩 (팝업 뜨는 순간 로딩)
			// Soft Object Ptr을 실제 메모리에 올립니다.
			UTexture2D* LoadedTexture = Data.Thumbnail.LoadSynchronous();

			// 3. 이미지 위젯에 적용
			if (LoadedTexture)
			{
				PreviewImage->SetBrushFromTexture(LoadedTexture);
			}
		}
		else
		{
			// 이미지가 없으면 기본값이나 빈칸 처리 (선택사항)
			// PreviewImage->SetBrushFromTexture(nullptr); 
		}
	}
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
