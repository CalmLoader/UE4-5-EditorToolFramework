// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorToolSetBPLibrary.h"
#include "DesktopPlatformModule.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "GeneralProjectSettings.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"
#include "libxl.h"
#include "Internationalization/Regex.h"
using namespace libxl;

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


void UEditorToolSetBPLibrary::ReadExcelFile(const FString& ExcelFilePath)
{
	FPlatformProcess::PushDllDirectory(*(GetToolSetPluginBasePath() / TEXT("ThirdParty/LibXL/BIN/bin64/")));
	void* LibXLHandle = FPlatformProcess::GetDllHandle(TEXT("libxl.dll"));
	if (LibXLHandle)
	{
		UE_LOG(LogTemp, Log, TEXT("UEditorToolSetBPLibrary, ReadExcelFile, LoadLibXLHandle Success"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UEditorToolSetBPLibrary, ReadExcelFile, LoadLibXLHandle Failed"));
		return;
	}

	// typedef bool (*RunLoadProc)(const wchar_t* a);
	// if (RunLoadProc RunLoad = static_cast<RunLoadProc>(FPlatformProcess::GetDllExport(LibXLHandle, TEXT("xlBookLoadInfoW"))))
	// {
	// 	RunLoad(*ExcelFilePath);
	// }
	if(Book* MyBook = xlCreateXMLBook())
	{
		if(MyBook->load(*ExcelFilePath))
		{
			if(Sheet* MySheet = MyBook->getSheet(0))
			{
				const FString RowContent11 = MySheet->readStr(1,1);
				UE_LOG(LogTemp, Log, TEXT("UEditorToolSetBPLibrary, ReadExcelFile:%s"), *RowContent11);
			}
		}
	}
	FPlatformProcess::FreeDllHandle(LibXLHandle);
	LibXLHandle = nullptr;
}

void UEditorToolSetBPLibrary::GetVersionInfo(FString& VersionInfo)
{
	//git
	const FString URL(TEXT("git.exe"));
	const FString FullCommand(FString::Printf(TEXT("-C %s log -1"), *GetToolSetPluginBasePath()));

	//svn
	// FString URL(TEXT("svn.exe"));
	// FString FullCommand(FString::Printf(TEXT("info %s"), *GetToolSetPluginBasePath()));

	int32 ReturnCode;
	FString OutResults;
	FString OutErrors;
	FPlatformProcess::ExecProcess(*URL, *FullCommand, &ReturnCode, &OutResults, &OutErrors);
	const FString ProjectVersion = UGeneralProjectSettings::StaticClass()->GetDefaultObject<UGeneralProjectSettings>()->ProjectVersion;
	FRegexPattern RegexPattern(TEXT("commit ((\\d|\\w)*)"));
	FRegexMatcher RegexMatcher(RegexPattern, OutResults);
	FString CommitHash(TEXT("0"));
	if(RegexMatcher.FindNext())
	{
		CommitHash = RegexMatcher.GetCaptureGroup(1);
	}
	FString TimeStr(TEXT("0"));
	RegexPattern = FRegexPattern(TEXT("Date.*?(\\d{2}:\\d{2}:\\d{2}.*?\\d{4}).*"));
	RegexMatcher = FRegexMatcher(RegexPattern, OutResults);
	if(RegexMatcher.FindNext())
	{
		TimeStr = RegexMatcher.GetCaptureGroup(1);
	}
	VersionInfo = FString::Printf(TEXT("%s|%s|%s"), *ProjectVersion, *CommitHash, *TimeStr);
	UE_LOG(LogTemp, Log, TEXT("UEditorToolSetBPLibrary, GetVersionInfo, %s"), *VersionInfo);
}
