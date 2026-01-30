// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/InventoryItemData.h"
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

	// 내 멤버 변수 갱신
	MyID = Data->ID;
	bIsOwned = Data->bIsOwned;

    // 1. 표시할 텍스쳐와 정보 찾기
    UTexture2D* TargetIcon = nullptr;
    EItemRarity TargetRarity = EItemRarity::Common;
    int32 TargetLevel = 1;

    if (Data->bIsCharacter)
    {
        if (!Data->CharacterData.FaceIcon.IsNull())
        {
            TargetIcon = Data->CharacterData.FaceIcon.LoadSynchronous();
        }
        TargetRarity = Data->CharacterData.Rank;
        TargetLevel = Data->Level;
    }
    else
    {
        if (!Data->ItemData.Icon.IsNull())
        {
            TargetIcon = Data->ItemData.Icon.LoadSynchronous();
        }
        TargetRarity = Data->ItemData.Rarity;
        TargetLevel = Data->EnhancementLevel;
    }

    // 2. ★ [핵심 해결책] 빨간 네모 코드의 "강제성"을 데이터에 적용
    // SetBrushFromTexture 대신, 브러시를 직접 만들어서 꽂아버립니다. (가장 확실함)
    if (TargetIcon)
    {
        FSlateBrush NewBrush;
        NewBrush.SetResourceObject(TargetIcon);          // 데이터에서 가져온 진짜 얼굴
        NewBrush.ImageSize = FVector2D(150.f, 180.f);    // 크기 고정
        NewBrush.DrawAs = ESlateBrushDrawType::Image;    // ★ 무조건 이미지로 그려라! (Box/Border 금지)
        NewBrush.TintColor = FLinearColor::White;        // 색상은 원본 그대로

        IconImage->SetBrush(NewBrush);

        // 투명화 완전 차단
        IconImage->SetColorAndOpacity(FLinearColor::White);
        IconImage->SetRenderOpacity(1.0f);
        IconImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    }
    else
    {
        // 텍스쳐가 없는 경우 (디버깅용 빨간색 표시)
        // 만약 화면에 빨간색만 나온다면 -> csv 파일의 경로가 틀린 겁니다.
        IconImage->SetColorAndOpacity(FLinearColor::Red);
    }

    // 3. 등급 테두리 (Border 전용)
    if (RarityBorder)
    {
        RarityBorder->SetBrushColor(GetRarityColor(TargetRarity));
        RarityBorder->SetContentColorAndOpacity(FLinearColor::White); // 투명화 방지
    }

    // 4. 레벨 텍스트
    if (LevelText)
    {
        if (bIsOwned)
        {
            FString LevelStr = Data->bIsCharacter ?
                FText::AsNumber(TargetLevel).ToString() :
                FString::Printf(TEXT("+%d"), TargetLevel);
            LevelText->SetText(FText::FromString(LevelStr));
            LevelText->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            LevelText->SetVisibility(ESlateVisibility::Collapsed);
        }
    }

    // 5. 버튼 및 잠금 상태
    if (bIsOwned)
    {
        if (LockOverlay) LockOverlay->SetVisibility(ESlateVisibility::Collapsed);
        if (SlotBtn)
        {
            SlotBtn->SetVisibility(ESlateVisibility::Visible);
            SlotBtn->SetIsEnabled(true);
        }
    }
    else
    {
        // 미보유 시 아이콘 어둡게
        if (IconImage) IconImage->SetColorAndOpacity(FLinearColor(0.2f, 0.2f, 0.2f, 1.0f));

        //if (LockOverlay) LockOverlay->SetVisibility(ESlateVisibility::Visible);

        if (SlotBtn)
        {
            SlotBtn->SetVisibility(ESlateVisibility::Visible);
            SlotBtn->SetIsEnabled(false);
        }
    }
}

void UInventorySlotWidget::OnClicked()
{
	if (bIsOwned)
	{
		UE_LOG(LogTemp, Log, TEXT("[Inventory] Item Selected: %s"), *MyID.ToString());
		// TODO: 여기서 메인 위젯이나 컨트롤러에게 "나 클릭됐어!"라고 알려주는 로직 추가 예정
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