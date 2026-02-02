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
	// 1. 데이터가 없으면? -> 그냥 하늘색 배경만 보여야 함 (내용물 숨김)
	if (!InData)
	{
		if (ContentBox) ContentBox->SetVisibility(ESlateVisibility::Collapsed);
		if (BlurImage) BlurImage->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	// 2. 데이터가 있으면? -> 내용물과 블러를 켬!
	if (ContentBox) ContentBox->SetVisibility(ESlateVisibility::Visible);
	if (BlurImage) BlurImage->SetVisibility(ESlateVisibility::Visible);

	// 3. 텍스트 갱신 (이미지 변경 코드는 삭제됨!)
	if (DetailNameText)
	{
		// FCharacterUIData나 FItemUIData 안의 이름이나 설명 텍스트를 가져오세요.
		// 예시: 
		FText InfoText = InData->bIsCharacter ? InData->CharacterData.Name : InData->ItemData.DisplayName;
		DetailNameText->SetText(InfoText);
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
