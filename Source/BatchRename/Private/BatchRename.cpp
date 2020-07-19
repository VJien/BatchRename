// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatchRename.h"
#include "BatchRenameStyle.h"
#include "BatchRenameCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "SRename.h"

static const FName BatchRenameTabName("BatchRename");

#define LOCTEXT_NAMESPACE "FBatchRenameModule"

void FBatchRenameModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FBatchRenameStyle::Initialize();
	FBatchRenameStyle::ReloadTextures();

	FBatchRenameCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FBatchRenameCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FBatchRenameModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FBatchRenameModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(BatchRenameTabName, FOnSpawnTab::CreateRaw(this, &FBatchRenameModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FBatchRenameTabTitle", "BatchRename"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FBatchRenameModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FBatchRenameStyle::Shutdown();

	FBatchRenameCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(BatchRenameTabName);
}

TSharedRef<SDockTab> FBatchRenameModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FBatchRenameModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("BatchRename.cpp"))
		);
		if (m_RenameWidget)
		{
			m_RenameWidget->Clear();
		}
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SAssignNew(m_RenameWidget,SRename)
		];
}

void FBatchRenameModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(BatchRenameTabName);
}

void FBatchRenameModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FBatchRenameCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FBatchRenameCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBatchRenameModule, BatchRename)