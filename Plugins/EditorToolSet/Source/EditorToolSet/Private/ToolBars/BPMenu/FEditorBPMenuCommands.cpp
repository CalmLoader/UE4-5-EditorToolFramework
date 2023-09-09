// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolBars/BPMenu/FEditorBPMenuCommands.h"
#define LOCTEXT_NAMESPACE "FEditorBPMenuCommands"
FEditorBPMenuCommands::~FEditorBPMenuCommands()
{
}

void FEditorBPMenuCommands::RegisterCommands()
{
	UI_COMMAND(BPMenuShowMessage, "BPMenuShowMessage", "BPMenuShowMessage Help", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(BPMenuOpenWindow, "BPMenuOpenWindow", "BPMenuOpenWindow Help", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(BPMenuChooseFolder, "BPMenuChooseFolder", "BPMenuChooseFolder Help", EUserInterfaceActionType::Button, FInputGesture());
}
#undef LOCTEXT_NAMESPACE