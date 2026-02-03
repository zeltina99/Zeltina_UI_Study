
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/InGame/CharacterStatusWidget.h" // ★ UHT 인식을 위해 Include
#include "PartyStatusPanel.generated.h"

/**
 * @class UPartyStatusPanel
 * @brief 좌측 상단 파티원 3명의 상태창을 그룹화한 패널.
 */
UCLASS()
class UI_TEST_API UPartyStatusPanel : public UUserWidget
{
	GENERATED_BODY()

public:
#pragma region 초기화
	virtual void NativeConstruct() override;
#pragma endregion 초기화

public:
#pragma region 데이터 업데이트
	/**
	 * @brief 특정 캐릭터의 상태(HP, MP)를 갱신합니다.
	 * @param Index 캐릭터 번호 (0, 1, 2)
	 * @param HP 현재 체력
	 * @param MaxHP 최대 체력
	 * @param MP 현재 마나
	 * @param MaxMP 최대 마나
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Party")
	void UpdateMemberStatus(int32 Index, float HP, float MaxHP, float MP, float MaxMP);
#pragma endregion 데이터 업데이트

protected:
#pragma region UI 컴포넌트
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCharacterStatusWidget> CharStatus_A = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCharacterStatusWidget> CharStatus_B = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCharacterStatusWidget> CharStatus_C = nullptr;
#pragma endregion UI 컴포넌트

private:
#pragma region 내부 상태
	/** @brief 관리를 편하게 하기 위한 배열 캐시 */
	TArray<TObjectPtr<UCharacterStatusWidget>> StatusWidgets;
#pragma endregion 내부 상태
};
