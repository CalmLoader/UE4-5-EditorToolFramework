// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolBars/MainMenu/FEditorMainMenuBar.h"
#include "LevelEditor.h"
#include "ToolBars/MainMenu/FEditorMainMenuCommands.h"

FEditorMainMenuBar::FEditorMainMenuBar()
{
	ToolName = FText::FromString(TEXT("MainTools"));
}

void FEditorMainMenuBar::BindController(FEditorMainMenuController* Controller)
{
	EditorMainMenuController = Controller;
}

void FEditorMainMenuBar::Initialize()
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(FName("LevelEditor"));
	TSharedRef<FExtender> MenuExtender = MakeShareable(new FExtender);
	MenuExtender->AddMenuBarExtension("Help", EExtensionHook::After, EditorMainMenuController->GetCommandList(), FMenuBarExtensionDelegate::CreateRaw(this, &FEditorMainMenuBar::BuildMenubar));
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void FEditorMainMenuBar::BuildMenubar(FMenuBarBuilder& MenuBarBuilder)
{
	//添加下拉菜单
	MenuBarBuilder.AddPullDownMenu(
		ToolName,
		FText::GetEmpty(),
		FNewMenuDelegate::CreateRaw(this, &FEditorMainMenuBar::FillPullDownMenu));
}

void FEditorMainMenuBar::FillPullDownMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddSubMenu(
		FText::FromString(TEXT("Common")),
		FText::GetEmpty(),
		FNewMenuDelegate::CreateLambda([](FMenuBuilder& MenuBuilder)
		{
			MenuBuilder.AddMenuEntry(FEditorMainMenuCommands::Get().MainMenuShowMessage);
			MenuBuilder.AddMenuEntry(FEditorMainMenuCommands::Get().MainMenuChooseFolder);
		}));
	
	MenuBuilder.AddMenuEntry(FEditorMainMenuCommands::Get().MainMenuOpenWindow);
	MenuBuilder.AddSeparator();
	MenuBuilder.BeginSection(FName("S"), FText::FromString("Others"));
	{
		MenuBuilder.AddEditableText(
			FText::FromString("EditableText"),
			FText::FromString("EditableText_Tips"),
			FSlateIcon(),
			FText::FromString("Hello Editor!!!")
		);
		MenuBuilder.AddWidget(SNew(SImage),FText::FromString("ImageWidget"));
	}
	MenuBuilder.EndSection();
}

