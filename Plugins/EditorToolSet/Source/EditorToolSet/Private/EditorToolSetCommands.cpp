// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorToolSetCommands.h"

#define LOCTEXT_NAMESPACE "FEditorToolSetModule"

void FEditorToolSetCommands::RegisterCommands()
{
	UI_COMMAND(DoSomething01, "EditorToolSet01", "Execute EditorToolSet action", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(DoSomething02, "EditorToolSet02", "Execute EditorToolSet action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
