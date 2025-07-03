#include "SCustomSlateWidget.h"
#include "Framework/Application/SlateApplication.h"
#include "Brushes/SlateColorBrush.h"
#include "Fonts/FontMeasure.h"
#include "Styling/AppStyle.h"

/* 매크로 구현 */
SLATE_IMPLEMENT_WIDGET(SCustomSlateWidget)

/* Attribute 시스템 초기화 (빈 함수지만 꼭 필요) */
void SCustomSlateWidget::PrivateRegisterAttributes(FSlateAttributeInitializer&)
{}

/* ───────── 입력 ───────── */

FReply SCustomSlateWidget::OnMouseButtonDown(const FGeometry& MyGeometry,
                                             const FPointerEvent& MouseEvent)
{
    if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        LastMouseDownPos =
            MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());

        return FReply::Handled().CaptureMouse(SharedThis(this));
    }
    return FReply::Unhandled();
}

FReply SCustomSlateWidget::OnMouseMove(const FGeometry& MyGeometry,
                                       const FPointerEvent& MouseEvent)
{
    if (HasMouseCapture())
    {
        const TSharedPtr<SWindow> Window =
            FSlateApplication::Get().FindWidgetWindow(SharedThis(this));

        if (Window.IsValid())
        {
            const FVector2D LocalMouse =
                MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
            const FVector2D Delta = LocalMouse - LastMouseDownPos;
            Window->MoveWindowTo(Window->GetPositionInScreen() + Delta);
        }
        return FReply::Handled();
    }
    return FReply::Unhandled();
}

FReply SCustomSlateWidget::OnMouseButtonUp(const FGeometry&,
                                           const FPointerEvent&)
{
    return FReply::Handled().ReleaseMouseCapture();
}

/* ───────── 그리기 ───────── */

int32 SCustomSlateWidget::OnPaint(const FPaintArgs&,
                                  const FGeometry& Allotted,
                                  const FSlateRect& MyCullingRect,
                                  FSlateWindowElementList& Out,
                                  int32 LayerId,
                                  const FWidgetStyle&,
                                  bool) const
{
    // ① 배경 색 (호버 시 살짝 밝게)
    const FSlateBrush* WhiteBrush = FAppStyle::GetBrush("WhiteBrush");
    const FLinearColor Bg =
        IsHovered() ? FLinearColor(0.6f, 0.5f, 0.9f)
                    : FLinearColor(0.1f, 0.5f, 0.9f);

    FSlateDrawElement::MakeBox(
        Out, LayerId, Allotted.ToPaintGeometry(),
        WhiteBrush, ESlateDrawEffect::None, Bg);

    // ② 텍스트
    static const FSlateFontInfo Font =
        FCoreStyle::GetDefaultFontStyle("Bold", 30);
    FSlateDrawElement::MakeText(
        Out, LayerId + 1, Allotted.ToPaintGeometry(),
        FText::FromString(TEXT("Hello Slate")), Font,
        ESlateDrawEffect::None, FLinearColor::White);

    return LayerId + 2;
}
