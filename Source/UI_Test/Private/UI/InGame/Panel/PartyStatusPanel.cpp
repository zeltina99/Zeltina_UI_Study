// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Panel/PartyStatusPanel.h"

#pragma region 초기화
void UPartyStatusPanel::NativeConstruct()
{
	Super::NativeConstruct();

	// 배열에 담아서 인덱스(0, 1, 2)로 접근하기 편하게 만듦
	StatusWidgets.Empty();
	if (CharStatus_A) StatusWidgets.Add(CharStatus_A);
	if (CharStatus_B) StatusWidgets.Add(CharStatus_B);
	if (CharStatus_C) StatusWidgets.Add(CharStatus_C);
}
#pragma endregion 초기화

#pragma region 데이터 업데이트
void UPartyStatusPanel::UpdateMemberStatus(int32 Index, float HP, float MaxHP, float MP, float MaxMP)
{
	// 인덱스 유효성 검사 (Safety)
	if (StatusWidgets.IsValidIndex(Index) && StatusWidgets[Index])
	{
		StatusWidgets[Index]->UpdateStatus(HP, MaxHP, MP, MaxMP);
	}
}
#pragma endregion 데이터 업데이트