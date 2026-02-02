// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Summon/SummonBannerWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"

#pragma region 초기화
void USummonBannerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 초기화 시 필요한 로직이 있다면 여기에 작성
}
#pragma endregion 초기화

#pragma region 공개 API
void USummonBannerWidget::UpdateBannerView(EGachaType TabType)
{
	// 1. 타이틀 텍스트 갱신 (Data-Driven: 텍스트 테이블이나 로컬라이징 키 사용 권장)
	if (TextBannerTitle)
	{
		FString TitleStr = (TabType == EGachaType::Character) ? TEXT("캐릭터 픽업 소환") : TEXT("무기 픽업 소환");
		TextBannerTitle->SetText(FText::FromString(TitleStr));
	}

	// 2. 배너 이미지 교체
	if (ImgBanner)
	{
		UTexture2D* TargetTexture = (TabType == EGachaType::Character) ? CharacterBannerTexture : WeaponBannerTexture;

		if (TargetTexture)
		{
			ImgBanner->SetBrushFromTexture(TargetTexture);
		}
	}
}

void USummonBannerWidget::UpdatePityText(int32 CurrentPity, int32 MaxPity)
{
	if (TextPityCount)
	{
		// 남은 횟수 계산
		int32 Remain = FMath::Max(0, MaxPity - CurrentPity);

		// 텍스트 포맷팅: "전설 확정까지 {0}회"
		FString Msg = FString::Printf(TEXT("전설 확정까지 %d회"), Remain);
		TextPityCount->SetText(FText::FromString(Msg));
	}
}
#pragma endregion 공개 API
