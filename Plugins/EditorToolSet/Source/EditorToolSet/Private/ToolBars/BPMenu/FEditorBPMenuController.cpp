// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolBars/BPMenu/FEditorBPMenuController.h"

#include "ToolBars/BPMenu/FEditorBPMenuCommands.h"


FEditorBPMenuController::FEditorBPMenuController():CommandList(new FUICommandList)
{
	FEditorBPMenuCommands::Register();
}

FEditorBPMenuController::~FEditorBPMenuController()
{
	FEditorBPMenuCommands::Unregister();
}

TSharedRef<FUICommandList> FEditorBPMenuController::GetCommandList()
{
	return CommandList;
}

void FEditorBPMenuController::BindCommands()
{
	const auto& Commands = FEditorBPMenuCommands::Get();
	CommandList->MapAction(Commands.BPMenuShowMessage,
						   FExecuteAction::CreateRaw(this, &FEditorBPMenuController::BPMenuShowMessage));
	CommandList->MapAction(Commands.BPMenuOpenWindow,
						   FExecuteAction::CreateRaw(this, &FEditorBPMenuController::BPMenuOpenWindow));
	CommandList->MapAction(Commands.BPMenuChooseFolder,
						   FExecuteAction::CreateRaw(this, &FEditorBPMenuController::BPMenuChooseFolder));
}

void FEditorBPMenuController::BPMenuShowMessage()
{
	UE_LOG(LogTemp, Log, TEXT("BPMenuShowMessage"));
}

void FEditorBPMenuController::BPMenuOpenWindow()
{
	UE_LOG(LogTemp, Log, TEXT("BPMenuOpenWindow"));
}

void FEditorBPMenuController::BPMenuChooseFolder()
{
	UE_LOG(LogTemp, Log, TEXT("BPMenuChooseFolder"));
}
