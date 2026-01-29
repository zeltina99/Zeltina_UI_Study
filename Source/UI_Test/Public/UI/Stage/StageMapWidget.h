// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/Data/FStageData.h"
#include "StageMapWidget.generated.h"

class UStageNodeWidget;
class UStagePopupWidget;
class UDataTable;
class UButton;

/**
 * @class UWorldMapWidget
 * @brief 월드맵 전체를 관리하는 메인 위젯 클래스입니다.
 * @details 자식으로 배치된 StageNode들을 자동으로 찾아서 이벤트를 연결하고, 클릭 시 팝업을 띄웁니다.
 */
UCLASS()
class UI_TEST_API UStageMapWidget : public UUserWidget
{	
	GENERATED_BODY()
public:
	/**
	 * @brief 스테이지 정보가 담긴 데이터 테이블입니다. (에디터에서 할당)
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UDataTable> StageDataTable = nullptr;

	/**
	 * @brief 클릭 시 띄울 팝업 위젯 클래스입니다. (WBP_StagePopup 할당)
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	TSubclassOf<UStagePopupWidget> PopupClass = nullptr;

protected:
	/**
	 * @brief 위젯이 생성될 때 호출됩니다.
	 * @details 하위 위젯(Node)들을 순회하며 이벤트를 바인딩하고 잠금 상태를 초기화합니다.
	 */
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	/**
	 * @brief 스테이지 노드 위젯들이 담겨 있는 컨테이너 패널입니다.
	 * @details
	 * - 전체 위젯 트리를 검색(GetAllWidgets)하는 비용을 줄이기 위해 사용합니다.
	 * - 에디터에서 CanvasPanel, VerticalBox 등의 이름을 'NodeContainer'로 지정해야 합니다.
	 * - 이 패널의 직속 자식(Direct Children)만 순회하여 성능을 최적화합니다.
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UPanelWidget> NodeContainer;

private:
	/**
	 * @brief 로비로 돌아가는 뒤로 가기 버튼입니다.
	 * @note meta = (BindWidget)이 있으므로, 블루프린트에서 이름을 "BackBtn"으로 꼭 맞춰야 합니다.
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackBtn;

	/**
	 * @brief 뒤로 가기 버튼 클릭 시 호출됩니다.
	 */
	UFUNCTION()
	void OnBackClicked();

	/**
	 * @brief 노드가 클릭되었을 때 호출되는 콜백 함수입니다.
	 * @param StageIndex 클릭된 노드의 스테이지 번호
	 */
	UFUNCTION()
	void OnNodeClicked(int32 StageIndex);

	/**
	 * @brief 데이터 테이블에서 Index에 맞는 스테이지 정보를 찾습니다.
	 */
	FStageData* GetStageDataByIndex(int32 Index);
};
