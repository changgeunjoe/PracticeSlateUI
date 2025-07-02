// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class LOSTARKMOBILE_API SCircle: public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SCircle)
		: _Size(100.f) {}                   // 초기 크기 (px)
	SLATE_ATTRIBUTE(float, Size)        // 외부에서 바꿀 수 있게
SLATE_END_ARGS()

void Construct(const FArguments& InArgs)
	{
		Size = InArgs._Size;
        
		// 노란 원 브러시 준비 (한 번만)
		CircleBrush = MakeShared<FSlateImageBrush>(
			TEXT("/Script/Engine.Texture2D'/Game/Blueprint/UI/OIP.OIP'"),
			FVector2D(1,1));                // 1×1 짜리여도 OK, 어차피 스케일
	}

	/* 크기 요청 */
	virtual FVector2D ComputeDesiredSize(float) const override
	{
		const float S = Size.Get();          // 0.0~값  가져옴
		return { S, S };
	}

	/* 실제 그리기 */
	virtual int32 OnPaint(
		const FPaintArgs&, const FGeometry& Geo, const FSlateRect&,
		FSlateWindowElementList& Out, int32 Layer,
		const FWidgetStyle&, bool) const override
	{
		const float S = Size.Get();

		// 원하는 픽셀 크기로 PaintGeometry 생성
		FSlateDrawElement::MakeBox(
			Out, Layer,
			Geo.ToPaintGeometry(         // (위치, 크기) 전달
				FVector2D(S, S),
				FSlateLayoutTransform()),

			CircleBrush.Get(),
			ESlateDrawEffect::None,
			FLinearColor::Yellow);
		return Layer;
	}

	/** 외부에서 크기 갱신 후 Invalidate */
	void SetSize(float NewSize)
	{
		Size = NewSize;
		Invalidate(EInvalidateWidgetReason::Layout | EInvalidateWidgetReason::Paint);
	}

private:
	TAttribute<float>               Size;
	TSharedPtr<FSlateBrush>         CircleBrush;
};
