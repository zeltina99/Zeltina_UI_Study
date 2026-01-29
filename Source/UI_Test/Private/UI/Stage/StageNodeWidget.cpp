// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Stage/StageNodeWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UStageNodeWidget::InitializeNode(bool bIsLocked)
{
	if (bIsLocked)
	{
		// 잠금 상태 처리
		StageBtn->SetIsEnabled(false);
		if (LockIcon)
		{
			LockIcon->SetVisibility(ESlateVisibility::Visible);
		}
		// 버튼 틴트를 어둡게 변경하여 비활성화 느낌 강조
		StageBtn->SetBackgroundColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
	}
	else
	{
		// 해금 상태 처리
		StageBtn->SetIsEnabled(true);
		if (LockIcon)
		{
			LockIcon->SetVisibility(ESlateVisibility::Hidden);
		}
		StageBtn->SetBackgroundColor(FLinearColor::White);
	}

	if (StageNumberText)
	{
		StageNumberText->SetText(FText::AsNumber(TargetStageIndex));
	}
}

void UStageNodeWidget::SetNodeThumbnail(UTexture2D* NewTexture)
{
	if (StageBtn && NewTexture)
	{
		// 버튼의 "Normal(평상시)" 상태 스타일을 가져와서 이미지를 교체합니다.
		FButtonStyle Style = StageBtn->WidgetStyle;

		// 슬레이트 브러시(SlateBrush)에 텍스처 설정
		FSlateBrush Brush = Style.Normal;
		Brush.SetResourceObject(NewTexture);
		// 이미지 크기가 찌그러지지 않게 박스나 이미지 사이즈에 맞춤
		Brush.DrawAs = ESlateBrushDrawType::Box;

		// 변경된 스타일을 다시 버튼에 적용
		Style.Normal = Brush;
		Style.Hovered = Brush; // 마우스 올렸을 때도 같은 이미지
		Style.Pressed = Brush; // 눌렀을 때도 같은 이미지 (원하면 다르게 설정 가능)

		StageBtn->SetStyle(Style);
	}
}

void UStageNodeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StageBtn)
	{
		StageBtn->OnClicked.AddDynamic(this, &UStageNodeWidget::OnBtnClicked);
	}
}

void UStageNodeWidget::OnBtnClicked()
{
	// 델리게이트가 바인딩되어 있다면, 자신의 인덱스를 실어 방송
	if (OnStageSelected.IsBound())
	{
		OnStageSelected.Broadcast(TargetStageIndex);
	}
}
