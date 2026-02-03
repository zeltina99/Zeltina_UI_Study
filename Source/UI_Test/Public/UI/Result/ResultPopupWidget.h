// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "ResultPopupWidget.generated.h"


class UButton;
/**
 * @class UResultPopupWidget
 * @brief 전투 결과 화면을 표시하는 팝업 위젯입니다.
 * @details '로비로 돌아가기' 버튼을 누르면 클리어 정보를 저장하고 레벨을 이동합니다.
 */
UCLASS()
class UI_TEST_API UResultPopupWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
protected:
	/**
	 * @brief 로비로 돌아가는 버튼입니다.
	 * @note UE5 표준인 TObjectPtr을 사용합니다. 에디터에서 "ReturnToLobbyBtn" 이름으로 바인딩해야 합니다.
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ReturnToStageBtn;

	/**
	 * @brief 위젯이 초기화될 때(메모리에 올라갈 때) 호출됩니다.
	 * @details 버튼 클릭 이벤트를 바인딩합니다. (중복 방지)
	 */
	virtual void NativeOnInitialized() override;

private:
	/**
	 * @brief 로비 복귀 버튼 클릭 시 호출됩니다.
	 * @details 버튼을 비활성화하고, 게임 인스턴스에 진행도를 저장한 뒤 레벨을 이동합니다.
	 */
	UFUNCTION()
	void OnReturnClicked();
};
