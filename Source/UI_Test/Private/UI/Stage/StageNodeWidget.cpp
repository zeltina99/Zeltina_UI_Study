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
