// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARKMOBILE_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
protected:
	TSharedPtr<class SMainMenuSlate> MainMenuWidget;
	TSharedPtr<class SWidget> MenuWidgetContainer;

	virtual void BeginPlay() override;
	
};
