// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EditorToolSetBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class EDITORTOOLSET_API UEditorToolSetBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="EditorToolSet")
	static void OpenBPUtilityByPath(const FString& Path);

	UFUNCTION(BlueprintCallable, Category="EditorToolSet")
	static FString ChooseFolderByExplorer();

	UFUNCTION(BlueprintCallable, Category="EditorToolSet")
	static FString ChooseFileByExplorer();

	UFUNCTION(BlueprintCallable, Category="EditorToolSet")
	static FString GetToolSetPluginBasePath();

	//切分大文件，例如日志文件
	UFUNCTION(BlueprintCallable, Category="EditorToolSet")
	static void SplitBigFile(const FString& FilePath, const int64 SingleFileSize = 1024);

	UFUNCTION(BlueprintCallable, Category="EditorToolSet")
	static void ReadExcelFile(const FString& ExcelFilePath);
};
