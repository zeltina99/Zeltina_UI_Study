

#include "UI/Inventory/InventoryMainWidget.h"
#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/InventoryItemData.h" // 데이터 객체 헤더 필수!
#include "Components/TileView.h"           // WrapBox 대신 TileView 사용
#include "Components/Button.h"
#include "Framework/Data/InventoryStructs.h"

// [가정] GameInstance 헤더 (보유 목록 가져오기용)
// #include "Framework/MyGameInstance.h"

void UInventoryMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 탭 버튼 이벤트 연결
	if (TabCharacterBtn)
	{
		TabCharacterBtn->OnClicked.AddDynamic(this, &UInventoryMainWidget::OnTabCharacterClicked);
	}
	if (TabWeaponBtn)
	{
		TabWeaponBtn->OnClicked.AddDynamic(this, &UInventoryMainWidget::OnTabWeaponClicked);
	}

	// 시작하자마자 캐릭터 탭 보여주기
	ShowCharacterList();
}

void UInventoryMainWidget::ShowCharacterList()
{
	// TileView와 데이터 테이블이 연결되어 있는지 확인
	if (!ContentTileView || !CharacterDT) return;

	// 1. 기존 목록 싹 비우기
	ContentTileView->ClearListItems();

	// 2. [최적화] 보유 목록을 TMap으로 변환 (O(1) 초고속 검색을 위해)
	// 실제로는 GameInstance에서 TArray<FOwnedHeroData>를 가져와야 합니다.
	TArray<FOwnedHeroData> MyOwnedHeroes;
	// 예: MyOwnedHeroes = GetGameInstance()->GetMyHeroes();

	TMap<FName, const FOwnedHeroData*> OwnedMap;
	for (const FOwnedHeroData& Hero : MyOwnedHeroes)
	{
		OwnedMap.Add(Hero.HeroID, &Hero);
	}

	// 3. 데이터 테이블의 모든 행(Row) 순회
	TArray<FName> RowNames = CharacterDT->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FCharacterUIData* Data = CharacterDT->FindRow<FCharacterUIData>(RowName, TEXT("LoadCharacter"));
		if (!Data) continue;

		// 4. ★ 위젯을 직접 만드는 게 아니라, '데이터 객체'를 생성합니다!
		UInventoryItemData* ItemObj = NewObject<UInventoryItemData>(this);

		// 5. [최적화] Map에서 보유 여부 즉시 검색
		const FOwnedHeroData* OwnedData = OwnedMap.FindRef(RowName); // 없으면 nullptr

		if (OwnedData)
		{
			// 보유 중이면 레벨 정보까지 넣어서 초기화
			ItemObj->InitCharacter(RowName, *Data, true, OwnedData->Level);
		}
		else
		{
			// 미보유면 기본값으로 초기화
			ItemObj->InitCharacter(RowName, *Data, false, 1);
		}

		// 6. Tile View에 데이터 추가 (화면 갱신은 TileView가 알아서 함)
		ContentTileView->AddItem(ItemObj);
	}
}

void UInventoryMainWidget::ShowWeaponList()
{
	if (!ContentTileView || !WeaponDT) return;

	ContentTileView->ClearListItems();

	// [최적화] 무기 보유 목록 맵핑
	TArray<FOwnedItemData> MyOwnedItems;
	// 예: MyOwnedItems = GetGameInstance()->GetMyItems();

	TMap<FName, const FOwnedItemData*> OwnedItemMap;
	for (const FOwnedItemData& Item : MyOwnedItems)
	{
		OwnedItemMap.Add(Item.ItemID, &Item);
	}

	TArray<FName> RowNames = WeaponDT->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FItemUIData* Data = WeaponDT->FindRow<FItemUIData>(RowName, TEXT("LoadItem"));
		if (!Data) continue;

		UInventoryItemData* ItemObj = NewObject<UInventoryItemData>(this);

		const FOwnedItemData* OwnedData = OwnedItemMap.FindRef(RowName);

		if (OwnedData)
		{
			ItemObj->InitItem(RowName, *Data, true, OwnedData->EnhancementLevel);
		}
		else
		{
			ItemObj->InitItem(RowName, *Data, false, 0);
		}

		ContentTileView->AddItem(ItemObj);
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