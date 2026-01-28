// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/Data/FStageData.h"
#include "StagePopupWidget.generated.h"

class UTextBlock;
class UImage;
class UButton;

/**
 * @class UStagePopupWidget
 * @brief 스테이지 선택 시 상세 정보를 표시하고 입장을 처리하는 팝업 위젯입니다.
 */
UCLASS()
class UI_TEST_API UStagePopupWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief 데이터 테이블에서 읽어온 정보를 바탕으로 UI를 갱신합니다.
	 * @param Data 표시할 스테이지 데이터 구조체
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Logic")
	void UpdatePopupInfo(const FStageData& Data);

protected:
	virtual void NativeConstruct() override;

private:
	/**
	 * @brief 스테이지 제목 텍스트
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TitleText = nullptr;
	/**
	 * @brief 스테이지 설명 텍스트
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DescText = nullptr;
	/**
	 * @brief 스테이지 미리보기 이미지
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> PreviewImage = nullptr;
	/**
	 * @brief 게임 시작(입장) 버튼
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> EnterBtn = nullptr;
	/**
	 * @brief 팝업 닫기 버튼
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseBtn = nullptr;
	/**
	 * @brief 임장 버튼 클릭 시 사용할 레벨 이름입니다.
	 * @details UpdatePopupInfo 호출 시 캐싱됩니다.
	 */
	FName CurrentLevelName;
	/**
	 * @brief 입장 버튼 클릭 핸들러. 비동기 로딩을 요청합니다.
	 */
	UFUNCTION()
	void OnEnterClicked();
	/**
	 * @brief 닫기 버튼 클릭 핸들러. 비동기 로딩을 요청합니다.
	 */
	UFUNCTION()
	void OnCloseClicked();
};
