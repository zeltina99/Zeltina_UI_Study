// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Panel/ActionControlPanel.h"
#include "Components/Button.h"

#pragma region 데이터 업데이트

void UActionControlPanel::UpdateSkillCooldown(int32 SkillIndex, float CurrentTime, float MaxTime)
{
	// 0: Active, 1: Ultimate
	if (SkillIndex == 0 && SkillSlot_Active)
	{
		// 쿨타임 시작 로직 호출 (필요 시)
		// SkillSlot_Active->StartCooldown(); 
	}
	else if (SkillIndex == 1 && SkillSlot_Ultimate)
	{
		// SkillSlot_Ultimate->StartCooldown();
	}
}

void UActionControlPanel::UpdateTagButtons(int32 ActiveCharIndex)
{
	// 현재 사용 중인 캐릭터는 버튼 비활성화 (선택 사항)
	if (TagBtn_A) TagBtn_A->SetIsEnabled(ActiveCharIndex != 0);
	if (TagBtn_B) TagBtn_B->SetIsEnabled(ActiveCharIndex != 1);
	if (TagBtn_C) TagBtn_C->SetIsEnabled(ActiveCharIndex != 2);
}

#pragma endregion 데이터 업데이트