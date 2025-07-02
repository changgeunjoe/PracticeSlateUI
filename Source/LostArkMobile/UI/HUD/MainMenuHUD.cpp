// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MainMenuHUD.h"
#include "Ui/Slate/SMainMenuSlate.h"
#include "UI/Slate/SMainMenuSlate.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine && GEngine->GameViewport)
	{
		// slate 생성
		// .OwningHUD(this).TempVal(5)를 통해 Construct 함수의 InArgs에 파라메터를 넘겨준다.
		MainMenuWidget = SNew(SMainMenuSlate)
			.OwningHUD(this).TempVal(5);
		GEngine->GameViewport->AddViewportWidgetContent(
			SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MainMenuWidget.ToSharedRef()));
	}
}
