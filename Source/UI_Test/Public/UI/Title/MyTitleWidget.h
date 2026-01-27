// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyTitleWidget.generated.h"

class UButton;
class UWidgetAnimation;	// 애니메이션용 전방 선언

/**
 * @class UMyTitleWidget
 * @brief 게임의 타이틀 화면을 관리하는 위젯 클래스입니다.
 * @note 화면 전체를 덮는 투명 버튼을 통해 'Touch to Start'기능을 구현하며,
 * 텍스트 깜빡임 애니메이션을 재생합니다.
 */
UCLASS()
class UI_TEST_API UMyTitleWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	/**
	* @brief 위젯이 화면에 생성된 직후 호출되는 초기화 함수입니다.
	* @note 여기서 버튼 이벤트를 바인딩하고, 초기 애니메이션을 재생합니다.
	*/
	virtual void NativeConstruct() override;

	/**
	 * @brief 로비로 넘어갈 때 미리 로딩할 에셋 목록
	 * @details 기획자가 에디터에서 직접 텍스처, 사운드, 파티클 등을 추가할 수 있습니다.
	 * 여기에 등록된 에셋 용량만큼 로딩 바가 차오릅니다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TArray<TSoftObjectPtr<UObject>> PreloadAssets;

private:
	/**
	* @brief 화면 전체를 덮는 투명 버튼입니다.
	* @note meta = (BindWidget) 속성은 언리얼 에디터의 위젯 이름과 변수명이 일치해야 자동으로 연결됩니다.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ScreenTouchBtn = nullptr;

	/**
	* @brief 'Touch to Start' 텍스트를 깜빡이게 하는 애니메이션입니다.
	* @note Transient 키워드는 이 변수가 디스크에 저장(Serialize)될 필요가 없음을 의미합니다.
	* meta = (BindWidgetAnim)을 통해 에디터의 애니메이션 트랙과 연결됩니다.
	*/
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> BlinkAnim = nullptr;
	
	/**
	* @brief 화면(투명 버튼)을 터치했을 때 호출됩니다.
	* @details GameInstance를 통해 로비 레벨로 비동기 로딩을 시작합니다.
	*/
	UFUNCTION()
	void OnScreenTouched();

};
