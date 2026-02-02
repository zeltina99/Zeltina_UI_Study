// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryDetailWidget.h"
#include "UI/Inventory/InventoryItemData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UInventoryDetailWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 내부적으로 클릭 이벤트를 바인딩하고, 이를 외부 델리게이트로 토스합니다.
	if (BtnEquip)
	{
		BtnEquip->OnClicked.AddDynamic(this, &UInventoryDetailWidget::HandleSwapButtonClicked);
	}
}

void UInventoryDetailWidget::UpdateInfo(UInventoryItemData* InData)
{
	if (!InData)
	{
		SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	SetVisibility(ESlateVisibility::Visible);

	// 1. 이름 갱신
	if (DetailNameText)
	{
		DetailNameText->SetText(FText::FromName(InData->ID));
	}

	// 2. 이미지 갱신
	if (DetailImage)
	{
		UTexture2D* TargetTex = nullptr;

		// 데이터 타입 확인 및 텍스쳐 로드
		if (InData->bIsCharacter && !InData->CharacterData.FaceIcon.IsNull())
			TargetTex = InData->CharacterData.FaceIcon.LoadSynchronous();
		else if (!InData->bIsCharacter && !InData->ItemData.Icon.IsNull())
			TargetTex = InData->ItemData.Icon.LoadSynchronous();

		if (TargetTex)
		{
			// 브러시 최적화: 매번 새로 만들기보다, 텍스쳐만 교체하는 것이 좋으나
			// 안전성을 위해 브러시 재생성 방식을 사용 (UI 찌그러짐 방지)
			FSlateBrush NewBrush;
			NewBrush.SetResourceObject(TargetTex);
			NewBrush.DrawAs = ESlateBrushDrawType::Image;
			NewBrush.TintColor = FLinearColor::White;

			DetailImage->SetBrush(NewBrush);
		}
	}
}

void UInventoryDetailWidget::HandleSwapButtonClicked()
{
	// 구독자(MainWidget)에게 알림 발송
	if (OnSwapButtonClicked.IsBound())
	{
		OnSwapButtonClicked.Broadcast();
	}
}
