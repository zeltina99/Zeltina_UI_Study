// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/LobbyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Framework/MyGameInstance.h"
#include "Component/GachaComponent.h" // ★ 헤더 파일 포함 필수!
#include "Engine/AssetManager.h"        // ★ 필수: 비동기 로더 접근용
#include "Engine/StreamableManager.h"   // ★ 필수: 스트리머블 매니저

#pragma region 초기화

ALobbyPlayerController::ALobbyPlayerController()
{
	bShowMouseCursor = true;
	GachaComponent = CreateDefaultSubobject<UGachaComponent>(TEXT("GachaComponent"));
}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());

	// 1. 초기 화면 결정
	TSoftClassPtr<UUserWidget> TargetSoftClass = MainMenuWidgetClass;

	if (GI && GI->NextLobbyScreen == FName("StageMap"))
	{
		if (!StageMapWidgetClass.IsNull())
		{
			TargetSoftClass = StageMapWidgetClass;
		}
		GI->NextLobbyScreen = FName("Main");
	}

	// 2. 비동기 로딩 시작
	ChangeWidgetAsync(TargetSoftClass);
}

#pragma endregion 초기화

#pragma region UI 네비게이션

void ALobbyPlayerController::ShowScreen(FName ScreenName)
{
	TSoftClassPtr<UUserWidget> TargetClass = nullptr;

	if (ScreenName == "Main")           TargetClass = MainMenuWidgetClass;
	else if (ScreenName == "StageMap")  TargetClass = StageMapWidgetClass;
	else if (ScreenName == "Character") TargetClass = InventoryWidgetClass;
	else if (ScreenName == "Summon")    TargetClass = SummonPopupWidgetClass;
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[LobbyController] Unknown Screen: %s"), *ScreenName.ToString());
		return;
	}

	// 비동기 전환 요청
	ChangeWidgetAsync(TargetClass);
}

#pragma endregion UI 네비게이션

#pragma region 비동기 로딩 로직

void ALobbyPlayerController::ChangeWidgetAsync(TSoftClassPtr<UUserWidget> NewWidgetClass)
{
	// 1. 유효성 검사
	if (NewWidgetClass.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("❌ [LobbyController] Widget Class is NULL! Check BP."));
		return;
	}

	// 2. 최적화: 이미 로드된 에셋이라면 즉시 교체 (메모리에 있는 경우)
	if (NewWidgetClass.IsValid())
	{
		OnWidgetLoaded(NewWidgetClass);
		return;
	}

	// 3. 로딩 중 UI 표시 (여기서 '로딩중...' 위젯을 띄우면 완벽합니다)
	UE_LOG(LogTemp, Log, TEXT("[AsyncLoad] Start loading widget..."));

	// 4. 비동기 로드 요청 (RequestAsyncLoad)
	FStreamableManager& Streamable = UAssetManager::Get().GetStreamableManager();

	CurrentLoadHandle = Streamable.RequestAsyncLoad(
		NewWidgetClass.ToSoftObjectPath(), // 로드할 경로
		FStreamableDelegate::CreateUObject(this, &ALobbyPlayerController::OnWidgetLoaded, NewWidgetClass) // 콜백
	);
}

void ALobbyPlayerController::OnWidgetLoaded(TSoftClassPtr<UUserWidget> LoadedWidgetClass)
{
	// 1. 클래스 가져오기 (이미 로드되었으므로 Get()은 즉시 리턴됨)
	UClass* WidgetClass = LoadedWidgetClass.Get();

	if (!WidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("[AsyncLoad] Failed to resolve class from SoftPtr."));
		return;
	}

	// 2. 기존 위젯 제거
	if (CurrentWidgetInstance)
	{
		CurrentWidgetInstance->RemoveFromParent();
		CurrentWidgetInstance = nullptr;
	}

	// 3. 새 위젯 생성 및 부착
	CurrentWidgetInstance = CreateWidget<UUserWidget>(this, WidgetClass);
	if (CurrentWidgetInstance)
	{
		CurrentWidgetInstance->AddToViewport();

		// 입력 모드 설정
		FInputModeUIOnly Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(Mode);
		bShowMouseCursor = true;

		UE_LOG(LogTemp, Log, TEXT("[AsyncLoad] Widget changed successfully!"));
	}

	// 4. 로딩 핸들 초기화 (메모리 관리)
	CurrentLoadHandle.Reset();
}

#pragma endregion 비동기 로딩 로직