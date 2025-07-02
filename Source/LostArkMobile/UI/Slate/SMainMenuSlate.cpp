#include "SMainMenuSlate.h"

#include "SCircle.h"
#include "UI/HUD/MainMenuHUD.h"
#include "GameFramework/PlayerController.h"

// localize for all languages
#define LOCTEXT_NAMESPACE "MainMenu"

void SMainMenuSlate::Construct(const FArguments & InArgs)
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
		   .Text_Lambda([](){                
			   return FText::FromString("Slate");
		   })      
	   ]
		+ SHorizontalBox::Slot()
	  .Padding(ButtonPadding)
	  .AutoWidth()          .VAlign(VAlign_Center)
	  [
	  	CircleWidget.ToSharedRef()
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