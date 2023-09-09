// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorToolSet.h"
#include "EditorToolSetStyle.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"


static const FName EditorToolSetTabName("EditorToolSet");

#define LOCTEXT_NAMESPACE "FEditorToolSetModule"

void FEditorToolSetModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FEditorToolSetStyle::Initialize();
	FEditorToolSetStyle::ReloadTextures();

	EditorMainMenuController = new FEditorMainMenuController;
	EditorMainMenuBar = new FEditorMainMenuBar;
	
	EditorBPMenuController = new FEditorBPMenuController;
	EditorBPMenuBar = new FEditorBPMenuBar;
	
	OpenConsoleCommand = MakeShareable(new FOpenConsoleCommand);
	OpenConsoleCommand->RegisterAllConsoleCommands();

	OnPostEngineInitHandle = FCoreDelegates::OnPostEngineInit.AddRaw(this, &FEditorToolSetModule::OnPostEngineInit);
}

void FEditorToolSetModule::ShutdownModule()
{
	OpenConsoleCommand->UnRegisterAllConsoleCommands();

	FEditorToolSetStyle::Shutdown();
}

void FEditorToolSetModule::OnPostEngineInit()
{
	InitMainMenuTool();
	InitBPMenuTool();
}

void FEditorToolSetModule::InitMainMenuTool()
{
	EditorMainMenuBar->BindController(EditorMainMenuController);
	EditorMainMenuController->BindCommands();
	EditorMainMenuBar->Initialize();
}

void FEditorToolSetModule::InitBPMenuTool()
{
	EditorBPMenuBar->BindController(EditorBPMenuController);
	EditorBPMenuController->BindCommands();
	EditorBPMenuBar->Initialize();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorToolSetModule, EditorToolSet)