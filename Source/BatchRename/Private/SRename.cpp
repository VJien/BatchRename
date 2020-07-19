// Fill out your copyright notice in the Description page of Project Settings.


#include "SRename.h"
#include "SlateOptMacros.h"
#include "Kismet/KismetStringLibrary.h"
#include "ContentBrowserModule.h"
#include "Modules/ModuleManager.h"
#include "IAssetTools.h"
#include "AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Input/SEditableText.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/Layout/SScaleBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SRename::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
	SNew(SOverlay)
		+ SOverlay::Slot()

		[
			SNew(SBox)
			.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.WidthOverride(300.f)
		.HeightOverride(800.f)

		[
			SNew(SVerticalBox)
		//****************************************
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.FillWidth(0.2f)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)
		[
			SNew(SButton)
			.OnClicked(this, &SRename::OnRenameClicked)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("VJ", "Rename", "Rename"))
			.Justification(ETextJustify::Center)
		]

		]
	//Prefix
	+ SHorizontalBox::Slot()
		.FillWidth(0.1f)
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FColor(0, 255,255))
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)

		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("VJ", "Prefix", "Prefix"))

		]
		]
	+ SHorizontalBox::Slot()
		.FillWidth(0.2f)
		[

			SNew(SBorder)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SEditableText)
				.OnTextChanged(this, &SRename::PretChanged)
			]

		]
	//....................
	//Name
	+ SHorizontalBox::Slot()
		.FillWidth(0.1f)
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FColor(0, 255, 255))
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("VJ", "Name", "Name"))
		]
		]
	+ SHorizontalBox::Slot()
		.FillWidth(0.2f)
		[

			SNew(SBorder)
			[
				SNew(SEditableText)
				.OnTextChanged(this, &SRename::NameTextChanged)
			]

		]
//..................


	//StartIndex
	+ SHorizontalBox::Slot()
		.FillWidth(0.25f)
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FColor(0, 255, 255))
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("VJ", "StartIndex", "StartIndex"))

		]
		]
	+ SHorizontalBox::Slot()
		.FillWidth(0.2f)
		[

			SNew(SBorder)
			[
				SNew(SEditableText)
				.Text(FText::FromString(TEXT("0")))
				.OnTextChanged(this, &SRename::NameStartIndexChanged)
			]

		]
	//....................

	//Suffix
	+ SHorizontalBox::Slot()
		.FillWidth(0.1f)
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FColor(0, 255,255))
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("VJ", "Suffix", "Suffix"))

		]
		]
	+ SHorizontalBox::Slot()
		.FillWidth(0.2f)
		[

			SNew(SBorder)
			[
				SNew(SEditableText)
				.OnTextChanged(this, &SRename::SufTextChanged)
			]

		]
	//....................


		]
		+ SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.AutoHeight()
			[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
				[
					SNew(SBorder)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
				[

					SNew(SScaleBox)
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Left)
					[
						SAssignNew(InfoBoxL, STextBlock)
						.AutoWrapText(true)
					]
				
				]
				]

			+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.ColorAndOpacity(FColor(0,255,0))
				[
					SNew(SScaleBox)
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Left)
					[
						SAssignNew(InfoBoxR, STextBlock)
						.AutoWrapText(true)
					]
					

				]
				
				]
			]
		]
		]

	];


	Init();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SRename::NameTextChanged(const FText& t)
{	
	name = t;
	UpdateNewName();
}

void SRename::SufTextChanged(const FText& t)
{
	suf = t;
	UpdateNewName();
}

void SRename::PretChanged(const FText& t)
{
	pre = t;
	UpdateNewName();
}

void SRename::NameStartIndexChanged(const FText& t)
{
	startIdx=UKismetStringLibrary::Conv_StringToInt(t.ToString());
	UpdateNewName();
}

FReply SRename::OnRenameClicked()
{

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	if (selectedAssets.Num() > 0 && NewNameList.Num()>0)
	{
		for (int32 i = 0; i < selectedAssets.Num(); ++i)
		{
			UObject* AssetObj = selectedAssets[i].GetAsset();
			TArray<FAssetRenameData> AssetsAndNames;
			const FString PackagePath = FPackageName::GetLongPackagePath(AssetObj->GetOutermost()->GetName());
			new(AssetsAndNames) FAssetRenameData(AssetObj, PackagePath, NewNameList[i]);
			AssetToolsModule.Get().RenameAssetsWithDialog(AssetsAndNames);

		}
	
		
	}


	return FReply::Handled();
}

void SRename::Init()
{
	if (!bIsInit)
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		ContentBrowserModule.GetOnAssetSelectionChanged().AddRaw(this, &SRename::OnAssetsChanged);
	}
	
}

void SRename::Clear()
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	ContentBrowserModule.GetOnAssetSelectionChanged().RemoveAll(this);
	
}

void SRename::OnAssetsChanged(const TArray<FAssetData>& asset, bool bIsPrimaryBrowser)
{
	selectedAssets = asset;
	FString info;
	for (auto i : asset)
	{
		UE_LOG(LogTemp, Log, TEXT("select asset £º %s"), *UKismetStringLibrary::Conv_NameToString(i.AssetName));
		info.Append(UKismetStringLibrary::Conv_NameToString(i.AssetName));
		info.Append(TEXT("\n"));
	}
	InfoBoxL->SetText(FText::FromString(info));

	UpdateNewName();
	

}

void SRename::UpdateNewName()
{
	NewNameList.Empty();
	if (selectedAssets.Num() > 0)
	{
		for (int32 i = 0; i < selectedAssets.Num(); ++i)
		{
			UObject* AssetObj = selectedAssets[i].GetAsset();
			TArray<FAssetRenameData> AssetsAndNames;
			FString newName = name.ToString();
			if (selectedAssets.Num() > 1)
			{
				newName.Append(TEXT("_"));
				newName.AppendInt(i + startIdx);
			}

			const FString PackagePath = FPackageName::GetLongPackagePath(AssetObj->GetOutermost()->GetName());

			if (!pre.IsEmpty())
			{
				FString preName = pre.ToString();
				preName.Append(newName);
				newName = preName;

			}
			if (!suf.IsEmpty())
			{
				newName.Append(suf.ToString());
			}

			NewNameList.Add(newName);

		}
	}
	if (NewNameList.Num() > 0)
	{
		FString NewInfo;
		for (int32 i = 0; i < NewNameList.Num(); ++i)
		{
			NewInfo.Append(NewNameList[i]);
			NewInfo.Append(TEXT("\n"));
		}
		InfoBoxR->SetText(FText::FromString(NewInfo));
	}
}
