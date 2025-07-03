#pragma once

#include "CoreMinimal.h"
#include "Widgets/SLeafWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"   // SNew, SAssignNew 매크로
#include "Input/Reply.h"

/**
 * 드래그-가능 & 호버 색상 변경하는 간단 Slate 리프 위젯
 */
class LOSTARKMOBILE_API SCustomSlateWidget : public SLeafWidget
{
	SLATE_DECLARE_WIDGET(SCustomSlateWidget, SLeafWidget)

public:
	SLATE_BEGIN_ARGS(SCustomSlateWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		SetCursor(EMouseCursor::GrabHand);    // 손 모양 커서
	}

	/* ───── 입력 오버라이드 ───── */
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry,
									 const FPointerEvent& MouseEvent) override;

	virtual FReply OnMouseMove(const FGeometry& MyGeometry,
							   const FPointerEvent& MouseEvent) override;

	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry,
								   const FPointerEvent& MouseEvent) override;

	/* ───── 렌더 & 레이아웃 ───── */
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& Allotted,
						  const FSlateRect& MyCullingRect, FSlateWindowElementList& Out,
						  int32 LayerId, const FWidgetStyle& InWidgetStyle,
						  bool bParentEnabled) const override;

	virtual FVector2D ComputeDesiredSize(float) const override
	{
		return FVector2D(200.f, 60.f);        // 기본 위젯 크기
	}

	/* 필수 – 새 Attribute 시스템용 Stub */


private:
	FVector2D LastMouseDownPos = FVector2D::ZeroVector;
};
