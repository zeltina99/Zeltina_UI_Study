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
	 * @brief 외부에서 이미지를 받아서 버튼의 배경으로 설정하는 함수
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Logic")
	void SetNodeThumbnail(UTexture2D* NewTexture);

protected:
	/**
	 * @brief 위젯 초기화 시 버튼 이벤트를 바인딩합니다.
	 */
	virtual void NativeConstruct()override;

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
