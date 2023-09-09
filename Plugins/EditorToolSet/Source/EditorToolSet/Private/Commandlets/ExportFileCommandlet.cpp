// Fill out your copyright notice in the Description page of Project Settings.


#include "Commandlets/ExportFileCommandlet.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"

int32 UExportFileCommandlet::Main(const FString& Params)
{
	TArray<FString> Tokens;
	TArray<FString> Switches;
	TMap<FString, FString> ParamsMap;
	ParseCommandLine(*Params, Tokens, Switches, ParamsMap);
	const FString Content = ParamsMap[TEXT("content")];
	SaveFile(Content);
	return 0;
}

void UExportFileCommandlet::SaveFile(const FString& ContentStr) const
{
	const FString Directory = IPluginManager::Get().FindPlugin(TEXT("EditorToolSet"))->GetBaseDir() / TEXT("Saved");
	IFileManager& FileManager = IFileManager::Get();
	if (!FileManager.DirectoryExists(*Directory))
	{
		FileManager.MakeDirectory(*Directory);
	}
	const FString FileName(TEXT("Test"));
	const FString FilePath = FString::Printf(TEXT("%s/%s.txt"), *Directory, *FileName);
	if (!FFileHelper::SaveStringToFile(ContentStr, *FilePath))
	{
		UE_LOG(LogTemp, Log, TEXT("SaveFailed"));
	}
}
