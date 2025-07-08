#include "SResizableBox.h"
#include "Rendering/DrawElements.h"
//#include "Widgets/SlateAttribute.h"     
SLATE_IMPLEMENT_WIDGET(SResizableBox)

/* ---------- Attribute 등록 ---------- */
void SResizableBox::PrivateRegisterAttributes(FSlateAttributeInitializer& Init)
{

}


/* ---------- Construct ---------- */
void SResizableBox::Construct(const FArguments& InArgs)
{
Size=FVector2D(200.f, 60.f);
	//FVector2D  NewSize = InArgs._InitSize;
	//Size.Assign(*this, InArgs._InitSize);

	SetCursor(EMouseCursor::GrabHand);
}

/* ---------- 입력 처리 ---------- */
FReply SResizableBox::OnMouseButtonDown(const FGeometry&, const FPointerEvent& Event)
{
	if (Event.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bResizing      = true;
		DragStartMouse = Event.GetScreenSpacePosition();
		DragStartSize  = Size;

		return FReply::Handled().CaptureMouse(SharedThis(this));
	}
	return FReply::Unhandled();
}

FReply SResizableBox::OnMouseMove(const FGeometry&, const FPointerEvent& Event)
{
	if (bResizing && HasMouseCapture())
	{
		const FVector2D Delta   = Event.GetScreenSpacePosition() - DragStartMouse;
		FVector2D       NewSize = DragStartSize + Delta;

		NewSize.X = FMath::Max(NewSize.X, 50.f);   // 최소 가로
		NewSize.Y = FMath::Max(NewSize.Y, 25.f);   // 최소 세로

		Size= NewSize; // ★
		Invalidate(EInvalidateWidgetReason::Layout | EInvalidateWidgetReason::Paint);

		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FReply SResizableBox::OnMouseButtonUp(const FGeometry&, const FPointerEvent& Event)
{
	if (bResizing && Event.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bResizing = false;
		return FReply::Handled().ReleaseMouseCapture();
	}
	return FReply::Unhandled();
}

/* ---------- 렌더 ---------- */
int32 SResizableBox::OnPaint(const FPaintArgs&, const FGeometry& Geo,
							  const FSlateRect&, FSlateWindowElementList& Out,
							  int32 Layer, const FWidgetStyle&, bool) const
{
	FSlateDrawElement::MakeBox(
		Out, Layer,
		Geo.ToPaintGeometry(Size, FSlateLayoutTransform()),
		FCoreStyle::Get().GetBrush("WhiteBrush"),
		ESlateDrawEffect::None,
		FLinearColor(0.2f, 0.4f, 1.f, 0.8f)   // 파란 반투명
	);
	return Layer;
}

/* ---------- 크기 반환 ---------- */
FVector2D SResizableBox::ComputeDesiredSize(float) const
{
	return Size;
}
