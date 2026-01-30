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
		// 잠겨 있을 때 텍스트 안 보임
		if(StageNumberText)
		{
			StageNumberText->SetVisibility(ESlateVisibility::Hidden);
		}
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
		// 해금 되면 텍스트가 보임
		if (StageNumberText) 
		{
			StageNumberText->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	}
}

void UStageNodeWidget::SetNodeIcon(UTexture2D* NewIcon)
{
	if (StageBtn && NewIcon)
	{
		// 버튼의 스타일 정보를 가져옵니다.
		FButtonStyle Style = StageBtn->WidgetStyle;

		// 슬레이트 브러시(SlateBrush)에 아이콘 텍스처 설정
		FSlateBrush Brush = Style.Normal;
		Brush.SetResourceObject(NewIcon);
		Brush.DrawAs = ESlateBrushDrawType::Box; // 구겨지지 않게 박스 형태로

		// 변경된 이미지를 모든 상태(평상시, 마우스오버, 눌림)에 적용
		Style.Normal = Brush;
		Style.Hovered = Brush;
		Style.Pressed = Brush;

		// 최종 스타일 적용
		StageBtn->SetStyle(Style);
	}
}

void UStageNodeWidget::SetStageName(FText NewName)
{
	if (StageNumberText)
	{
		StageNumberText->SetText(NewName);
	}
}

void UStageNodeWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UStageNodeWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

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
