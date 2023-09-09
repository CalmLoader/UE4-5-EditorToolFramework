// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorConsoleCommands/Commands/FShowWindowCommand.h"

#include "Interfaces/IMainFrameModule.h"


FShowWindowCommand::FShowWindowCommand()
{
	CommandName = TEXT("ShowWindow");
	HelpContent = TEXT("ShowWindowHelp");
}

FShowWindowCommand::~FShowWindowCommand()
{
}

void FShowWindowCommand::Execute(const TArray<FString>& Args)
{
	FEditorCommandBase::Execute(Args);

	FString WindowTitle;
	for (int i = 0; i < Args.Num(); i++)
	{
		WindowTitle.Append(Args[i]);
	}
	const TSharedRef<SWindow> CookbookWindow = SNew(SWindow)
		.Title(FText::FromString(WindowTitle))
		.ClientSize(FVector2D(800, 400))
		.SupportsMaximize(false)
		.SupportsMinimize(false);
	const IMainFrameModule& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));
	if (MainFrameModule.GetParentWindow().IsValid())
	{
		FSlateApplication::Get().AddWindowAsNativeChild(CookbookWindow, MainFrameModule.GetParentWindow().ToSharedRef());
	}
	else
	{
		FSlateApplication::Get().AddWindow(CookbookWindow);
	}
}
