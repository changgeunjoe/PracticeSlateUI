// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */

class AMainMenuHUD;
class LOSTARKMOBILE_API SMainMenuSlate : public SCompoundWidget//“슬롯 하나만 가진” 베이스 클래스. 다중 슬롯은 SPanel 상속.
{

public:

	SLATE_BEGIN_ARGS(SMainMenuSlate) {}
	
	// Construct 시 OwningHUD의 대한 Argument를 앞에 under bar가 붙은 형태로 생성해준다. ex) InArgs._OwningHUD
	SLATE_ARGUMENT(TWeakObjectPtr<class AMainMenuHUD>, OwningHUD)
	SLATE_ARGUMENT(float, TempVal)
	SLATE_END_ARGS()

	// slate class는 생성자와 소멸자를 사용하지 않고 Construct를 사용하여 생성시키도록 한다.
	void Construct(const FArguments& InArgs);
	virtual bool SupportsKeyboardFocus() const override { return true; }
	FReply OnQuitClicked() const;


private:
	TWeakObjectPtr<class AMainMenuHUD> OwningHUD;
	float TempVal{};
	/** Circle 을 나중에 접근하려면 포인터 보관 */
	TSharedPtr<class SCircle> CircleWidget;
};
