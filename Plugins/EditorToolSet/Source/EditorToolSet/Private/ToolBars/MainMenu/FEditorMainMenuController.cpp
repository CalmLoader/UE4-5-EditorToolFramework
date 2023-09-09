// Fill out your copyright notice in the Description page of Project Settings.
#include "ToolBars/MainMenu/FEditorMainMenuController.h"

#include "EditorToolSetBPLibrary.h"
#include "ToolBars/MainMenu/FEditorMainMenuCommands.h"

FEditorMainMenuController::FEditorMainMenuController():CommandList(new FUICommandList)
{
	FEditorMainMenuCommands::Register();
}

FEditorMainMenuController::~FEditorMainMenuController()
{
	FEditorMainMenuCommands::Unregister();
}

void FEditorMainMenuController::MainMenuShowMessage()
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("MainMenuShowMessage")));
}

void FEditorMainMenuController::MainMenuOpenWindow()
{
	UEditorToolSetBPLibrary::OpenBPUtilityByPath(TEXT("EditorUtilityWidgetBlueprint'/EditorToolSet/BP_RootEditorUtility.BP_RootEditorUtility'"));
}

void FEditorMainMenuController::MainMenuChooseFolder()
{
	const FString Path = UEditorToolSetBPLibrary::ChooseFolderByExplorer();
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Path));
}

TSharedRef<FUICommandList> FEditorMainMenuController::GetCommandList()
{
	return CommandList;
}

void FEditorMainMenuController::BindCommands()
{
	const auto& Commands = FEditorMainMenuCommands::Get();
	CommandList->MapAction(Commands.MainMenuOpenWindow,
	                       FExecuteAction::CreateRaw(this, &FEditorMainMenuController::MainMenuOpenWindow));
	CommandList->MapAction(Commands.MainMenuShowMessage,
	                       FExecuteAction::CreateRaw(this, &FEditorMainMenuController::MainMenuShowMessage));
	CommandList->MapAction(Commands.MainMenuChooseFolder,
						   FExecuteAction::CreateRaw(this, &FEditorMainMenuController::MainMenuChooseFolder));
}
