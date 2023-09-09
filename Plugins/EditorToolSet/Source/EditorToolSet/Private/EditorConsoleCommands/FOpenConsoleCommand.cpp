// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorConsoleCommands/FOpenConsoleCommand.h"
#include "EditorConsoleCommands/Commands/FShowMessageCommand.h"
#include "EditorConsoleCommands/Commands/FShowWindowCommand.h"


FOpenConsoleCommand::FOpenConsoleCommand()
{
	FShowMessageCommand* ShowMessageCommand = new FShowMessageCommand();
	EditorCommands.Add(ShowMessageCommand);
	FShowWindowCommand* ShowWindowCommand = new FShowWindowCommand();
	EditorCommands.Add(ShowWindowCommand);
}

FOpenConsoleCommand::~FOpenConsoleCommand()
{
	for (int i = EditorCommands.Num() - 1; i >= 0; i--)
	{
		delete EditorCommands[i];
	}
	EditorCommands.Empty();
}

void FOpenConsoleCommand::RegisterAllConsoleCommands()
{
	for (int i = 0; i < EditorCommands.Num(); i++)
	{
		FEditorCommandBase* EditorCommand = EditorCommands[i];
		FConsoleCommandWithArgsDelegate ConsoleCommandWithArgsDelegate = FConsoleCommandWithArgsDelegate::CreateLambda(
			[EditorCommand](const TArray<FString>& Args)
			{
				if (EditorCommand)
				{
					EditorCommand->Execute(Args);
				}
			});
		IConsoleCommand* Command = IConsoleManager::Get().RegisterConsoleCommand(*EditorCommand->CommandName
			, *EditorCommand->HelpContent, ConsoleCommandWithArgsDelegate, ECVF_Default);
		ConsoleCommands.Add(Command);
	}
}

void FOpenConsoleCommand::UnRegisterAllConsoleCommands()
{
	for (int i = ConsoleCommands.Num() - 1; i >= 0; i--)
	{
		IConsoleManager::Get().UnregisterConsoleObject(ConsoleCommands[i]);
		ConsoleCommands[i] = nullptr;
	}
	ConsoleCommands.Empty();
}
