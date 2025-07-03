#include "SMainMenuSlate.h"

#include "SCircle.h"
#include "UI/HUD/MainMenuHUD.h"
#include "GameFramework/PlayerController.h"

// localize for all languages
#define LOCTEXT_NAMESPACE "MainMenu"

void SMainMenuSlate::Construct(const FArguments& InArgs)
{
	// 생성될 때 받은 argument들이 InArgs를 통해 들어온다.
	// InArgs._TempVal
	// InArgs._OwningHUD

	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(500.f, 300.f);
	const FMargin ButtonPadding = FMargin(10.f);

	// localize "My Title Name" by key "GameTitle"
	const FText TitleText = LOCTEXT("GameTitle", "My Title Name");
	const FText QuitText = LOCTEXT("QuitGame", "Quit Game");

	// get unreal core style by FCoreStyle
	// FCoreStyle 를 통해 언리얼 코어 스타일을 사용할 수 있다.
	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;

	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 40.f;

	SAssignNew(CircleWidget, SCircle);
	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Hello"))
		]
		+ SHorizontalBox::Slot()
		[
			SNew(STextBlock)
			.Text_Lambda([]()
			{
				return FText::FromString("Slate");
			})
		]
		+ SHorizontalBox::Slot()
		.Padding(ButtonPadding)
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			CircleWidget.ToSharedRef()
		]
		/* ④ 새로 추가한 SButton */
		+ SHorizontalBox::Slot()
		.Padding(ButtonPadding)
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.Text(FText::FromString("Click Me"))
			.OnClicked_Lambda([]()
			{
				UE_LOG(LogTemp, Log, TEXT("Button pressed!"));
				return FReply::Handled();
			})
		]
		/* ⑤ 가로 스크롤바 추가 */
		+ SHorizontalBox::Slot()
		.Padding(ButtonPadding)
		.FillWidth(1.f) // 가로 길이는 남는 공간
		[
			SNew(SBox)
			.HeightOverride(16.f) // ← 바 높이 강제 확보
			[
				SNew(SScrollBar)
				                .Orientation(Orient_Horizontal)
				                .Thickness(FVector2D(8.f, 8.f))
				                .AlwaysShowScrollbar(true) // 5.4+ (있는 버전이면 켜 주기)
				                .OnUserScrolled_Lambda([](float Off)
				                {
					                UE_LOG(LogTemp, Log, TEXT("Offset %.2f"), Off);
				                })
			]
		]
	];
}

FReply SMainMenuSlate::OnQuitClicked() const
{
	if (OwningHUD.IsValid())
	{
		if (APlayerController* PC = OwningHUD->PlayerOwner)
		{
			PC->ConsoleCommand("quit");
		}
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
