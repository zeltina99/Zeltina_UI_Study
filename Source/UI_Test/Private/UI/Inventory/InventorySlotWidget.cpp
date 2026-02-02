// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/InventoryItemData.h"
#include "UI/Inventory/InventoryMainWidget.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UInventorySlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// [Event Binding] 버튼 클릭 이벤트 연결	
	if (SlotBtn)
	{
		SlotBtn->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnClicked);
	}
}

// ★ Tile View가 데이터를 갱신할 때 호출하는 핵심 함수
void UInventorySlotWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UInventoryItemData* Data = Cast<UInventoryItemData>(ListItemObject);
	if (!Data) return;

	// 1. 데이터 캐싱
	MyID = Data->ID;
	bIsOwned = Data->bIsOwned;

	// 2. 각 기능별 함수 호출 (분업화)
	UpdateIcon(Data);    // 그림 그려!
	UpdateVisuals(Data); // 글씨 써!
	UpdateState(bIsOwned); // 버튼 켜/꺼!
}

void UInventorySlotWidget::UpdateIcon(UInventoryItemData* Data)
{
	if (!IconImage) return;

	UTexture2D* TargetIcon = nullptr;

	// 데이터 타입에 따라 아이콘 로드
	if (Data->bIsCharacter)
	{
		if (!Data->CharacterData.FaceIcon.IsNull())
			TargetIcon = Data->CharacterData.FaceIcon.LoadSynchronous();
	}
	else
	{
		if (!Data->ItemData.Icon.IsNull())
			TargetIcon = Data->ItemData.Icon.LoadSynchronous();
	}

	// 아이콘 적용 (강제 이미지 모드)
	if (TargetIcon)
	{
		FSlateBrush NewBrush;
		NewBrush.SetResourceObject(TargetIcon);
		NewBrush.ImageSize = FVector2D(210.f, 340.f); // ★ 210x340 크기 적용!
		NewBrush.DrawAs = ESlateBrushDrawType::Image; // ★ 강제 Image 모드
		NewBrush.TintColor = FLinearColor::White;

		IconImage->SetBrush(NewBrush);

		// 초기화 (투명도 등)
		IconImage->SetColorAndOpacity(FLinearColor::White);
		IconImage->SetRenderOpacity(1.0f);
		IconImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		// 데이터 없음 (에러 표시: 빨강)
		IconImage->SetColorAndOpacity(FLinearColor::Red);
	}
}

void UInventorySlotWidget::UpdateVisuals(UInventoryItemData* Data)
{
	// A. 등급 테두리 표시
	if (RarityBorder)
	{
		if (bIsOwned)
		{
			// 보유 중이면 원래 등급 색상 표시
			EItemRarity Rarity = Data->bIsCharacter ? Data->CharacterData.Rank : Data->ItemData.Rarity;
			RarityBorder->SetBrushColor(GetRarityColor(Rarity));
		}
		else
		{
			// ★ [수정] 미보유 시 회색 테두리로 덮어씀
			RarityBorder->SetBrushColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		}

		RarityBorder->SetContentColorAndOpacity(FLinearColor::White);
	}

	// B. 레벨 텍스트 표시
	if (LevelText)
	{
		if (bIsOwned)
		{
			int32 LevelVal = Data->bIsCharacter ? Data->Level : Data->EnhancementLevel;
			FString LevelStr = Data->bIsCharacter ?
				FText::AsNumber(LevelVal).ToString() :
				FString::Printf(TEXT("+%d"), LevelVal);

			LevelText->SetText(FText::FromString(LevelStr));
			LevelText->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			LevelText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UInventorySlotWidget::UpdateState(bool bOwned)
{
	// A. 자물쇠 오버레이 (미보유 시 블러 처리용)
	// ★ [수정] 여기가 핵심입니다. 미보유 시 보이게(Visible), 보유 시 숨김(Collapsed)
	if (LockOverlay)
	{
		LockOverlay->SetVisibility(bOwned ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
	}

	// B. 보유 상태 처리
	if (bOwned)
	{
		// [보유 중] 밝게 표시, 버튼 활성
		if (IconImage) IconImage->SetColorAndOpacity(FLinearColor::White);

		if (SlotBtn)
		{
			SlotBtn->SetVisibility(ESlateVisibility::Visible);
			SlotBtn->SetIsEnabled(true);
		}
	}
	else
	{
		// [미보유] 어둡게 표시(Dimmed), 버튼 비활성
		// ★ 아이콘을 어둡게(0.3) 죽여서 회색 느낌을 더해줍니다.
		if (IconImage) IconImage->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));

		if (SlotBtn)
		{
			SlotBtn->SetVisibility(ESlateVisibility::Visible);
			SlotBtn->SetIsEnabled(false);
		}
	}
}

void UInventorySlotWidget::OnClicked()
{
	if (!bIsOwned) return; // 미보유 시 반응 X

	UInventoryItemData* MyData = Cast<UInventoryItemData>(GetListItem());
	if (!MyData) return;

	// 상위 위젯 호출 (직통 전화)
	UInventoryMainWidget* MainWidget = Cast<UInventoryMainWidget>(GetTypedOuter<UInventoryMainWidget>());
	if (MainWidget)
	{
		// ★ 함수 이름이 바뀌었습니다! (UpdateDetailInfo -> OnInventorySlotClicked)
		// 이제 메인이 알아서 판단합니다 (정보를 보여줄지, 교체할지).
		MainWidget->OnInventorySlotClicked(MyData);
	}
}

FLinearColor UInventorySlotWidget::GetRarityColor(EItemRarity Rarity)
{
	switch (Rarity)
	{
	case EItemRarity::Common:    return FLinearColor(0.6f, 0.6f, 0.6f); // 회색
	case EItemRarity::Uncommon:  return FLinearColor(0.2f, 1.0f, 0.2f); // 녹색
	case EItemRarity::Rare:      return FLinearColor(0.2f, 0.2f, 1.0f); // 파랑
	case EItemRarity::Epic:      return FLinearColor(0.6f, 0.2f, 1.0f); // 보라
	case EItemRarity::Legendary: return FLinearColor(1.0f, 0.8f, 0.0f); // 금색
	default:                     return FLinearColor::White;
	}
}