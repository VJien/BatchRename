// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "AssetData.h"


/**
 * 
 */
class BATCHRENAME_API SRename : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRename)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void Clear();

private:
	// local value
	FText name;
	FText suf;
	FText pre;
	int32 startIdx=0;
	bool bIsInit=false;
	
	//Event boundd EditableTextBlock
	void NameTextChanged(const FText& t);
	void SufTextChanged(const FText& t);
	void PretChanged(const FText& t);
	void NameStartIndexChanged(const FText& t);
	// Rename Event
	FReply OnRenameClicked();

	void Init();
	
	void OnAssetsChanged(const TArray<FAssetData>& asset, bool bIsPrimaryBrowser);
	void UpdateNewName();
	TSharedPtr<class STextBlock> InfoBoxL;
	TSharedPtr<class STextBlock> InfoBoxR;

	TArray<FAssetData> selectedAssets;
	TArray<FString> NewNameList;

};
