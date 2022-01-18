// Copyright Epic Games, Inc. All Rights Reserved.

#include "StandaloneWindowEditorTool.h"

#include "BaseEditorTool.h"
#include "BaseToolEditorCustomization.h"
#include "StandaloneWindowEditorToolStyle.h"
#include "StandaloneWindowEditorToolCommands.h"
#include "LevelEditor.h"
#include "QuestActor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Engine/Selection.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"
#include "Widgets/Layout/SUniformGridPanel.h"

static const FName StandaloneWindowEditorToolTabName("StandaloneWindowEditorTool");

#define LOCTEXT_NAMESPACE "FStandaloneWindowEditorToolModule"

void FStandaloneWindowEditorToolModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.RegisterCustomClassLayout("BaseEditorTool", FOnGetDetailCustomizationInstance::CreateStatic(&FBaseToolEditorCustomization::MakeInstance));
	}
	FStandaloneWindowEditorToolStyle::Initialize();
	FStandaloneWindowEditorToolStyle::ReloadTextures();

	FStandaloneWindowEditorToolCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FStandaloneWindowEditorToolCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FStandaloneWindowEditorToolModule::PluginButtonClicked),
		FCanExecuteAction());

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands,
			FMenuExtensionDelegate::CreateRaw(this, &FStandaloneWindowEditorToolModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender());
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands,
			FToolBarExtensionDelegate::CreateRaw(this, &FStandaloneWindowEditorToolModule::AddToolbarExtension));

		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FStandaloneWindowEditorToolModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(StandaloneWindowEditorToolTabName, FOnSpawnTab::CreateRaw(this, &FStandaloneWindowEditorToolModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FStandaloneWindowEditorToolTabTitle", "StandaloneWindowEditorTool"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FStandaloneWindowEditorToolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FStandaloneWindowEditorToolStyle::Shutdown();

	FStandaloneWindowEditorToolCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(StandaloneWindowEditorToolTabName);
}

void FStandaloneWindowEditorToolModule::TriggerTool(UClass* ToolClass)
{
	UBaseEditorTool* ToolInstance = NewObject<UBaseEditorTool>(GetTransientPackage(), ToolClass);
	ToolInstance->AddToRoot();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	TArray<UObject*> ObjectsToView;
	ObjectsToView.Add(ToolInstance);
	TSharedRef<SWindow> Window = PropertyModule.CreateFloatingDetailsView(ObjectsToView, false);

	Window->SetOnWindowClosed(FOnWindowClosed::CreateStatic(&FStandaloneWindowEditorToolModule::OnToolWindowClosed, ToolInstance));
}

void FStandaloneWindowEditorToolModule::CreateToolListMenu(FMenuBuilder& MenuBuilder)
{
	for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		UClass* Class = *ClassIt;
		if (!Class->HasAnyClassFlags(CLASS_Deprecated) | (CLASS_Abstract))
		{
			if (Class->IsChildOf(UBaseEditorTool::StaticClass()))
			{
				FString FriendlyName = Class->GetName();
				FText MenuDescription = FText::Format(LOCTEXT("ToolMenuDescription","{0}"), FText::FromString(FriendlyName));
				FText MenuTooltip = FText::Format(LOCTEXT("ToolMenuTooltip", "Execute the {0} tool"), FText::FromString(FriendlyName));

				FUIAction Action(FExecuteAction::CreateStatic(&FStandaloneWindowEditorToolModule::TriggerTool, Class));

				MenuBuilder.AddMenuEntry(
				MenuDescription,
				MenuTooltip,
				FSlateIcon(),
				Action
				);
			}
		}
	}
}

void FStandaloneWindowEditorToolModule::OnToolWindowClosed(const TSharedRef<SWindow>& Window, UBaseEditorTool* Instance)
{
	Instance->RemoveFromRoot();
}

TSharedRef<SDockTab> FStandaloneWindowEditorToolModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	// FText WidgetText = FText::Format(
	// 	LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
	// 	FText::FromString(TEXT("FStandaloneWindowEditorToolModule::OnSpawnPluginTab")),
	// 	FText::FromString(TEXT("StandaloneWindowEditorTool.cpp"))
	// 	);

	FText WidgetText = FText::FromString("Move Selected Actors");
	FText WT = FText::FromString("TestButton");
	FText RightText = FText::FromString("Right Text Panel");
	TSharedRef<SHorizontalBox> HorizontalBox = SNew(SHorizontalBox);
	TSharedRef<SUniformGridPanel> UniformGridPanel = SNew(SUniformGridPanel);
	UniformGridPanel->AddSlot(0,0)
	[
		SNew(SButton)
		.Text(FText::FromString("FirstButton"))
		.OnClicked_Lambda([UniformGridPanel]()
		{
			if (GEditor)
			{
				TArray<AQuestActor*> Quests;
				for (auto Iter = GEditor->GetSelectedActorIterator(); Iter; ++ Iter)
				{
					auto Quest = Cast<AQuestActor>(*Iter);
					if (Quest)
					{
						Quests.Add(Quest);
					}
				}
				GEditor->SelectNone(false, true);
				for	(int32 i = 0; i < Quests.Num(); ++i)
				{
					GEditor->SelectActor(Quests[i],true,true);
					UniformGridPanel->AddSlot(1,i)
					[
						SNew(SButton)
						.Text(Quests[i]->Name)
					];
				}
			}
			return FReply::Handled();
		}
		)
	];
	UniformGridPanel->AddSlot(0,1)
	[
		SNew(SButton)
		.Text(FText::FromString("Second Button"))
	];
	HorizontalBox->AddSlot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	[
		UniformGridPanel
	];
	HorizontalBox->AddSlot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	[
		SNew(SButton)
		.Text(FText::FromString("Second Button Right"))
	];
	
	

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
		HorizontalBox
		];
}

void FStandaloneWindowEditorToolModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(StandaloneWindowEditorToolTabName);
}

void FStandaloneWindowEditorToolModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FStandaloneWindowEditorToolCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FStandaloneWindowEditorToolCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

void FStandaloneWindowEditorToolModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FStandaloneWindowEditorToolCommands::Get().OpenPluginWindow);
}

void FStandaloneWindowEditorToolModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FStandaloneWindowEditorToolCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStandaloneWindowEditorToolModule, StandaloneWindowEditorTool)