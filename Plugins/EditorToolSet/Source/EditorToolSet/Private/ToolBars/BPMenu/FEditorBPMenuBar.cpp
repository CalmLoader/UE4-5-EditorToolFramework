// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolBars/BPMenu/FEditorBPMenuBar.h"
#include "BlueprintEditorModule.h"
#include "ToolBars/BPMenu/FEditorBPMenuCommands.h"

FEditorBPMenuBar::FEditorBPMenuBar()
{
	ToolName = FText::FromString(TEXT("BPMenuTools"));
}

void FEditorBPMenuBar::Initialize()
{
	FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>(
		FName("Kismet"));
	auto& ExtenderDelegates = BlueprintEditorModule.GetMenuExtensibilityManager()->GetExtenderDelegates();
	ExtenderDelegates.Add(FAssetEditorExtender::CreateLambda(
		[&](const TSharedRef<FUICommandList>, const TArray<UObject*> ContextSensitiveObjects)
		{
			ContextObject = ContextSensitiveObjects.Num() < 1 ? nullptr : Cast<UBlueprint>(ContextSensitiveObjects[0]);
			TSharedRef<FExtender> ToolbarExtender(new FExtender());
			const auto ExtensionDelegate = FToolBarExtensionDelegate::CreateRaw(this, &FEditorBPMenuBar::BuildToolbar);
			ToolbarExtender->AddToolBarExtension("Debugging", EExtensionHook::After,
			                                     EditorBPMenuController->GetCommandList(), ExtensionDelegate);
			return ToolbarExtender;
		}));

	TSharedRef<FExtender> ToolbarExtender(new FExtender());
	const auto ExtensionDelegate = FMenuBarExtensionDelegate::CreateRaw(this, &FEditorBPMenuBar::BuildMenubar);
	ToolbarExtender->AddMenuBarExtension("Debug", EExtensionHook::After, EditorBPMenuController->GetCommandList(),
	                                     ExtensionDelegate);
	BlueprintEditorModule.GetMenuExtensibilityManager()->AddExtender(ToolbarExtender);
}

void FEditorBPMenuBar::BindController(FEditorBPMenuController* BPMenuController)
{
	EditorBPMenuController = BPMenuController;
}

void FEditorBPMenuBar::BuildMenubar(FMenuBarBuilder& MenuBarBuilder)
{
	MenuBarBuilder.AddPullDownMenu(
		ToolName,
		FText::GetEmpty(),
		FNewMenuDelegate::CreateLambda([](FMenuBuilder& MenuBuilder)
		{
			MenuBuilder.AddMenuEntry(FEditorBPMenuCommands::Get().BPMenuShowMessage);
			MenuBuilder.AddMenuEntry(FEditorBPMenuCommands::Get().BPMenuOpenWindow);
		})
	);
}

void FEditorBPMenuBar::BuildToolbar(FToolBarBuilder& ToolbarBuilder)
{
	ToolbarBuilder.BeginSection(NAME_None);
	const auto Blueprint = Cast<UBlueprint>(ContextObject);
	FString InStyleName(TEXT("Hello"));
	UE_LOG(LogTemp, Log, TEXT("InStyleName=%s"), *InStyleName);
	ToolbarBuilder.AddComboButton(
		FUIAction(),
		FOnGetContent::CreateLambda([&]()
		{
			const FEditorBPMenuCommands& Commands = FEditorBPMenuCommands::Get();
			FMenuBuilder MenuBuilder(true, EditorBPMenuController->GetCommandList());
			if (!1)
			{
				MenuBuilder.AddMenuEntry(Commands.BPMenuShowMessage);
			}
			else
			{
				MenuBuilder.AddMenuEntry(Commands.BPMenuShowMessage);
				MenuBuilder.AddMenuEntry(Commands.BPMenuOpenWindow);
				MenuBuilder.AddMenuEntry(Commands.BPMenuChooseFolder);
			}
			return MenuBuilder.MakeWidget();
		}),
		FText::FromString("ToolBar"),
		FText::FromString("ToolBarToolTip"),
		FSlateIcon("EditorStyle", *InStyleName)
	);
	ToolbarBuilder.EndSection();
}
