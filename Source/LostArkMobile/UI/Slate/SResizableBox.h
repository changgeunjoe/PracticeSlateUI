#pragma once

#include "CoreMinimal.h"
#include "Widgets/SLeafWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Input/Reply.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

/**
 * 드래그해서 크기를 조정할 수 있는 간단 Slate 리프 위젯
 */
class LOSTARKMOBILE_API SResizableBox : public SLeafWidget
{
	SLATE_DECLARE_WIDGET(SResizableBox, SLeafWidget)

public:

	/* ---------- 생성 파라미터 ---------- */
	SLATE_BEGIN_ARGS(SResizableBox)
		: _InitSize(FVector2D(200.f, 60.f))          // 초기 크기
	{}
	SLATE_ATTRIBUTE(FVector2D, InitSize)
SLATE_END_ARGS()

/* ---------- Slate 빌더 ---------- */
void Construct(const FArguments& InArgs);

	/* ---------- 입력 오버라이드 ---------- */
	virtual FReply OnMouseButtonDown(const FGeometry&, const FPointerEvent&) override;
	virtual FReply OnMouseMove      (const FGeometry&, const FPointerEvent&) override;
	virtual FReply OnMouseButtonUp  (const FGeometry&, const FPointerEvent&) override;

	/* ---------- 렌더 & 레이아웃 ---------- */
	virtual int32     OnPaint(const FPaintArgs&, const FGeometry&, const FSlateRect&,
							   FSlateWindowElementList&, int32, const FWidgetStyle&, bool) const override;
	virtual FVector2D ComputeDesiredSize(float) const override;

	/* ---------- (UE5+) Attribute 등록 ---------- */
	

private:
	/* 현재 위젯 크기 (동적으로 변함) */
	FVector2D Size;

	/* 드래그 상태 변수들 */
	bool      bResizing      = false;
	FVector2D DragStartMouse = FVector2D::ZeroVector;
	FVector2D DragStartSize  = FVector2D::ZeroVector;
};
