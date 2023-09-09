// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorToolSetBPLibrary.h"
#include "DesktopPlatformModule.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "Interfaces/IPluginManager.h"

void UEditorToolSetBPLibrary::OpenBPUtilityByPath(const FString& Path)
{
	if (UEditorUtilityWidgetBlueprint* EditorWidget = LoadObject<UEditorUtilityWidgetBlueprint>(nullptr, *Path))
	{
		UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
		EditorUtilitySubsystem->SpawnAndRegisterTab(EditorWidget);
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Cannot load the EditorUtilityWidgetBlueprint!"));
	}
}

FString UEditorToolSetBPLibrary::ChooseFolderByExplorer()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	FString OutputDirectory;
	const FString DefaultPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	UE_LOG(LogTemp, Log, TEXT("DefaultPath: %s"), *DefaultPath);
	bool successfullySelected = false;

	if (DesktopPlatform)
	{
		const void* ParentWindowWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

		successfullySelected = DesktopPlatform->OpenDirectoryDialog(
			ParentWindowWindowHandle,
			FString(TEXT("选择目录")),
			DefaultPath,
			OutputDirectory
		);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find the DesktopPlatform!"));
	}

	if (!successfullySelected)
	{
		return FString(TEXT(""));
	}

	FPaths::MakePathRelativeTo(OutputDirectory, *DefaultPath);
	OutputDirectory = TEXT("/Game/") + OutputDirectory;

	return OutputDirectory;
}

FString UEditorToolSetBPLibrary::GetToolSetPluginBasePath()
{
	return IPluginManager::Get().FindPlugin(TEXT("EditorToolSet"))->GetBaseDir();
}
