// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryMainWidget.h"
#include "UI/Inventory/InventorySlotWidget.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "Framework/Data/InventoryStructs.h" // 데이터 구조체

void UInventoryMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 탭 버튼 이벤트 바인딩
	if (TabCharacterBtn)
	{
		TabCharacterBtn->OnClicked.AddDynamic(this, &UInventoryMainWidget::OnTabCharacterClicked);
	}
	if (TabWeaponBtn)
	{
		TabWeaponBtn->OnClicked.AddDynamic(this, &UInventoryMainWidget::OnTabWeaponClicked);
	}

	// 초기 화면: 캐릭터 리스트 표시
	ShowCharacterList();
}

void UInventoryMainWidget::ShowCharacterList()
{
	if (!ContentGrid || !SlotClass || !CharacterDT)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryMainWidget: 필수 데이터나 위젯이 바인딩되지 않았습니다."));
		return;
	}

	// 1. 기존 목록 초기화
	ContentGrid->ClearChildren();

	// 2. 보유 데이터 가져오기 (예시: 더미 데이터 또는 GameInstance 호출)
	// 실제 구현 시: TArray<FOwnedHeroData> MyHeroes = GetGameInstance()->GetOwnedHeroes();
	TArray<FOwnedHeroData> MyDummyHeroes; // 테스트용 빈 배열 (모두 미보유로 뜸)

	// 3. 데이터 테이블의 모든 행(Row) 순회
	TArray<FName> RowNames = CharacterDT->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		// 데이터 조회
		FCharacterUIData* Data = CharacterDT->FindRow<FCharacterUIData>(RowName, TEXT("LoadCharacterData"));
		if (!Data) continue;

		// 보유 여부 확인 (람다 식 활용)
		const FOwnedHeroData* OwnedData = MyDummyHeroes.FindByPredicate([&](const FOwnedHeroData& Item) {
			return Item.HeroID == RowName;
			});

		// 4. 슬롯 위젯 생성 및 데이터 주입
		UInventorySlotWidget* NewSlot = CreateWidget<UInventorySlotWidget>(this, SlotClass);
		if (NewSlot)
		{
			NewSlot->InitCharacterSlot(RowName, *Data, OwnedData);
			ContentGrid->AddChildToWrapBox(NewSlot); // 그리드에 추가
		}
	}
}

void UInventoryMainWidget::ShowWeaponList()
{
	if (!ContentGrid || !SlotClass || !WeaponDT) return;

	ContentGrid->ClearChildren();

	// TODO: 실제 보유 아이템 목록 가져오기
	TArray<FOwnedItemData> MyDummyItems;

	TArray<FName> RowNames = WeaponDT->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FItemUIData* Data = WeaponDT->FindRow<FItemUIData>(RowName, TEXT("LoadItemData"));
		if (!Data) continue;

		const FOwnedItemData* OwnedData = MyDummyItems.FindByPredicate([&](const FOwnedItemData& Item) {
			return Item.ItemID == RowName;
			});

		UInventorySlotWidget* NewSlot = CreateWidget<UInventorySlotWidget>(this, SlotClass);
		if (NewSlot)
		{
			NewSlot->InitItemSlot(RowName, *Data, OwnedData);
			ContentGrid->AddChildToWrapBox(NewSlot);
		}
	}
}

void UInventoryMainWidget::OnTabCharacterClicked()
{
	ShowCharacterList();
}

void UInventoryMainWidget::OnTabWeaponClicked()
{
	ShowWeaponList();
}
