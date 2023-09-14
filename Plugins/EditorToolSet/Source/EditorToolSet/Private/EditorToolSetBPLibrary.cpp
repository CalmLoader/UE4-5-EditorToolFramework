// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorToolSetBPLibrary.h"
#include "DesktopPlatformModule.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"

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
	OutputDirectory.Empty();
	const FString DefaultPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	if (DesktopPlatform)
	{
		const void* ParentWindowWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
		if(DesktopPlatform->OpenDirectoryDialog(ParentWindowWindowHandle, FString(TEXT("选择目录")), DefaultPath, OutputDirectory))
		{
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find the DesktopPlatform!"));
	}
	return OutputDirectory;
}

FString UEditorToolSetBPLibrary::ChooseFileByExplorer()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	const FString DefaultPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	FString OutFilePath;
	OutFilePath.Empty();
	if (DesktopPlatform)
	{
		const void* ParentWindowWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
		TArray<FString> OutFiles;
		if (DesktopPlatform->OpenFileDialog(ParentWindowWindowHandle, TEXT("选择文件"), DefaultPath,TEXT(""), TEXT("*"),
		                                    EFileDialogFlags::None, OutFiles))
		{
			if (OutFiles.Num() == 1)
			{
				OutFilePath = FPaths::ConvertRelativePathToFull(OutFiles[0]);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find the DesktopPlatform!"));
	}
	return OutFilePath;
}

FString UEditorToolSetBPLibrary::GetToolSetPluginBasePath()
{
	return IPluginManager::Get().FindPlugin(TEXT("EditorToolSet"))->GetBaseDir();
}

void UEditorToolSetBPLibrary::SplitBigFile(const FString& FilePath, const int64 SingleFileSize)
{
	if (!IFileManager::Get().FileExists(*FilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("FilePath:%s is not exist or is a directory"), *FilePath);
		return;
	}
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	const int64 FileSize = PlatformFile.FileSize(*FilePath);
	const FString FullPath = FPaths::ConvertRelativePathToFull(FilePath);
	const FString BaseFilename = FPaths::GetBaseFilename(FullPath);
	const FString BasePath = FPaths::Combine(FPaths::GetPath(FullPath));
	const FString Extension = FPaths::GetExtension(FullPath, true);
	IFileHandle* FileHandle = PlatformFile.OpenRead(*FilePath);

	int32 FileIndex = 1;
	int64 Offset = 0;
	while (true)
	{
		FString CurrentFilename = BaseFilename + FString::FromInt(FileIndex);
		FString SplitFilePath = BasePath / CurrentFilename + Extension;
		IFileHandle* SingleFileHandle = PlatformFile.OpenWrite(*SplitFilePath);
		int64 Size = SingleFileSize;
		if (Offset + SingleFileSize >= FileSize)
		{
			Size = FileSize - Offset;
		}
		TArray<uint8> OutData;
		OutData.AddUninitialized(Size);
		bool bRead = FileHandle->Read(OutData.GetData(), Size);
		bool bWrite = SingleFileHandle->Write(OutData.GetData(), Size);
		SingleFileHandle->Flush(true);
		delete SingleFileHandle;
		if (Size != SingleFileSize)
		{
			break;
		}
		Offset += SingleFileSize;
		FileIndex++;
	}

	FileHandle->Flush();
	delete FileHandle;
}
