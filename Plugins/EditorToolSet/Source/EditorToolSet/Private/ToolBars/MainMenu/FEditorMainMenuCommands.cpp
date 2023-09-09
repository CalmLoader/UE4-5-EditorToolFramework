// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolBars/MainMenu/FEditorMainMenuCommands.h"
#define LOCTEXT_NAMESPACE "FEditorMainMenuCommands"

FEditorMainMenuCommands::~FEditorMainMenuCommands()
{
}

void FEditorMainMenuCommands::RegisterCommands()
{
	UI_COMMAND(MainMenuShowMessage, "MainMenuShowMessage", "MainMenuShowMessage Help", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(MainMenuOpenWindow, "MainMenuOpenWindow", "MainMenuOpenWindow Help", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(MainMenuChooseFolder, "MainMenuChooseFolder", "MainMenuChooseFolder Help", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
