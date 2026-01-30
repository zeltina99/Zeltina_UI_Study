// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/Data/FStageData.h"
#include "StageNodeWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;

/**
 * @brief 스테이지 노드가 클릭되었을 때 발생되는 델리게이트입니다.
 * @param StageIndex 선택된 스테이지의 고유 인덱스
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStageSelected, int32, StageIndex);

/**
 * @class UStageNodeWidget
 * @brief 월드맵 상에 배치되는 개별 스테이지 버튼 위젯입니다.
 * @details 잠금/해금 상태에 따라 아이콘이 변경되며, 클릭 시 부모 위젯에게 자신의 Index를 알립니다.
 */
UCLASS()
class UI_TEST_API UStageNodeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief 기획자가 에디터에서 설정하는 이 노드의 스테이지 번호입니다.
	 * @details 월드맵 위젯이 이 값을 읽어서 잠금 여부를 판단합니다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 TargetStageIndex = 1;

	/**
	 * @brief 버튼 클릭 이벤트를 외부로 전파하는 디스패처입니다.
	 */
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnStageSelected OnStageSelected;

	/**
	 * @brief 노드의 잠금/해금 상태를 시각적으로 업데이트합니다.
	 * @param bIsLocked true면 자물쇠 아이콘 표시 및 클릭 비활성화
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Logic")
	void InitializeNode(bool bIsLocked);

	/**
	 * @brief 지도 상의 노드 버튼에 표시될 작은 아이콘을 설정합니다.
	 * @details 데이터 테이블의 NodeIcon을 받아서 버튼 스타일(Normal, Hovered, Pressed)에 적용합니다.
	 * @param NewIcon 데이터 테이블에서 로드된 아이콘 텍스처
	 */
	UFUNCTION(BlueprintCallable, Category = "UI Logic")
	void SetNodeIcon(UTexture2D* NewIcon);

	/** 
	 * @brief 데이터 테이블에 있는 진짜 스테이지 이름(예: "1-1")을 설정합니다.
	 */
	UFUNCTION(BlueprintCallable)
	void SetStageName(FText NewName);

protected:
	/**
	 * @brief 위젯 초기화 시 버튼 이벤트를 바인딩합니다.
	 */
	virtual void NativeConstruct()override;

	virtual void NativeOnInitialized()override;

private:
	/**
	 * @brief 사용자가 터치하는 메인 버튼입니다.
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StageBtn = nullptr;

	/**
	 * @brief 잠금 상태일 때 표시되는 자물쇠 아이콘입니다.
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> LockIcon = nullptr;

	/**
	 * @brief 스테이지 번호를 표시하는 텍스트입니다.
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StageNumberText = nullptr;

	/**
	 * @brief 버튼 클릭 시 호출되는 내부 함수입니다. 델리게이트를 방송합니다.
	 */
	UFUNCTION()
	void OnBtnClicked();

};
