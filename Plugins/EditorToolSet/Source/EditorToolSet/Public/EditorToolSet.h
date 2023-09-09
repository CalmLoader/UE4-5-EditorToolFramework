// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorConsoleCommands/FOpenConsoleCommand.h"
#include "ToolBars/BPMenu/FEditorBPMenuBar.h"
#include "ToolBars/BPMenu/FEditorBPMenuController.h"
#include "ToolBars/MainMenu/FEditorMainMenuBar.h"
#include "ToolBars/MainMenu/FEditorMainMenuController.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FEditorToolSetModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<FOpenConsoleCommand> OpenConsoleCommand;

	void InitMainMenuTool();
	void InitBPMenuTool();
	
	//引擎初始化
	FDelegateHandle OnPostEngineInitHandle;
	void OnPostEngineInit();

	FEditorMainMenuController* EditorMainMenuController;
	FEditorMainMenuBar* EditorMainMenuBar;
	FEditorBPMenuController* EditorBPMenuController;
	FEditorBPMenuBar* EditorBPMenuBar;
};
