
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterStatusWidget.generated.h"

#pragma region 전방선언
class UImage;
class UProgressBar;
class UTexture2D;
#pragma endregion 전방선언

/**
 * @class UCharacterStatusWidget
 * @brief 인게임 좌측 상단 파티원 1명의 상태(HP/MP/초상화)를 표시하는 위젯.
 */
UCLASS()
class UI_TEST_API UCharacterStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:
#pragma region 초기화
	/**
	 * @brief 캐릭터 데이터 초기화
	 * @param Portrait 이미지 텍스처
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Status")
	void InitializeCharacter(UTexture2D* Portrait);
#pragma endregion 초기화

public:
#pragma region 상태 업데이트
	/**
	 * @brief HP/MP 바 갱신
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Status")
	void UpdateStatus(float CurHP, float MaxHP, float CurMP, float MaxMP);

	/**
	 * @brief 태그 상태 변경 (활성/대기/사망 시각화)
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Status")
	void SetActiveState(bool bIsActive, bool bIsDead);
#pragma endregion 상태 업데이트

protected:
#pragma region UI 컴포넌트
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> PortraitImg = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HPBar = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> MPBar = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> DimmedOverlay = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> DeadIcon = nullptr;
#pragma endregion UI 컴포넌트
};