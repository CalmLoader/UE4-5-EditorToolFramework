// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorConsoleCommands/Commands/FShowMessageCommand.h"


FShowMessageCommand::FShowMessageCommand()
{
	CommandName = TEXT("ShowMessage");
	HelpContent = TEXT("ShowMessageHelp");
}

FShowMessageCommand::~FShowMessageCommand()
{
}

void FShowMessageCommand::Execute(const TArray<FString>& Args)
{
	FEditorCommandBase::Execute(Args);
	FString Content;
	for (int i = 0; i < Args.Num(); i++)
	{
		Content.Append(Args[i]);
	}
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Content));
}
