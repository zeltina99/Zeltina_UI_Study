#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InGameHUDWidget.generated.h"

#pragma region 전방선언
class UPartyStatusPanel;
class USummonControlPanel;
class UActionControlPanel;
class UTextBlock;
class UButton;
#pragma endregion 전방선언

/**
 * @class UInGameHUDWidget
 * @brief 인게임 전체 UI를 총괄하는 컨테이너 위젯.
 * @details
 * - 극단적인 SRP 적용: 세부 위젯들을 직접 관리하지 않고, 기능별 'Panel' 위젯에게 위임(Delegate)한다.
 * - 유지보수: 소환 슬롯이 5개에서 10개가 되어도 이 클래스는 수정할 필요가 없다. (SummonPanel만 수정)
 */
UCLASS()
class UI_TEST_API UInGameHUDWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

};