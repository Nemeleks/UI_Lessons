// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestEditorModeEdModeToolkit.h"

#include "QuestEditorModeEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "EditorModeManager.h"
#include "NPCEditorSubsystem.h"
#include "Objective.h"
#include "QuestActor.h"
#include "QuestGiverActor.h"
#include "Editor/GroupActor.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "FQuestEditorModeEdModeToolkit"

FQuestEditorModeEdModeToolkit::FQuestEditorModeEdModeToolkit()
{
}

void FQuestEditorModeEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	struct Locals
	{
		static bool IsWidgetEnabled()
		{
			return GEditor->GetSelectedActors()->Num() != 0;
		}
	
	// 	static FReply OnButtonClick(FVector InOffset)
	// 	{
	// 		USelection* SelectedActors = GEditor->GetSelectedActors();
	//
	// 		// Let editor know that we're about to do something that we want to undo/redo
	// 		GEditor->BeginTransaction(LOCTEXT("MoveActorsTransactionName", "MoveActors"));
	//
	// 		// For each selected actor
	// 		for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
	// 		{
	// 			if (AActor* LevelActor = Cast<AActor>(*Iter))
	// 			{
	// 				// Register actor in opened transaction (undo/redo)
	// 				LevelActor->Modify();
	// 				// Move actor to given location
	// 				LevelActor->TeleportTo(LevelActor->GetActorLocation() + InOffset, FRotator(0, 0, 0));
	// 			}
	// 		}
	//
	// 		// We're done moving actors so close transaction
	// 		GEditor->EndTransaction();
	//
	// 		return FReply::Handled();
	// 	}
	//
	// 	static TSharedRef<SWidget> MakeButton(FText InLabel, const FVector InOffset)
	// 	{
	// 		return SNew(SButton)
	// 			.Text(InLabel)
	// 			.OnClicked_Static(&Locals::OnButtonClick, InOffset);
	// 	}
	};
	//
	// const float Factor = 256.0f;
	//
	// SAssignNew(ToolkitWidget, SBorder)
	// 	.HAlign(HAlign_Center)
	// 	.Padding(25)
	// 	.IsEnabled_Static(&Locals::IsWidgetEnabled)
	// 	[
	// 		SNew(SVerticalBox)
	// 		+ SVerticalBox::Slot()
	// 		.AutoHeight()
	// 		.HAlign(HAlign_Center)
	// 		.Padding(50)
	// 		[
	// 			SNew(STextBlock)
	// 			.AutoWrapText(true)
	// 			.Text(LOCTEXT("HelperLabel", "Select some actors and move them around using buttons below"))
	// 		]
	// 		+ SVerticalBox::Slot()
	// 			.HAlign(HAlign_Center)
	// 			.AutoHeight()
	// 			[
	// 				Locals::MakeButton(LOCTEXT("UpButtonLabel", "Up"), FVector(0, 0, Factor))
	// 			]
	// 		+ SVerticalBox::Slot()
	// 			.HAlign(HAlign_Center)
	// 			.AutoHeight()
	// 			[
	// 				SNew(SHorizontalBox)
	// 				+ SHorizontalBox::Slot()
	// 				.AutoWidth()
	// 				[
	// 					Locals::MakeButton(LOCTEXT("LeftButtonLabel", "Left"), FVector(0, -Factor, 0))
	// 				]
	// 				+ SHorizontalBox::Slot()
	// 					.AutoWidth()
	// 					[
	// 						Locals::MakeButton(LOCTEXT("RightButtonLabel", "Right"), FVector(0, Factor, 0))
	// 					]
	// 			]
	// 		+ SVerticalBox::Slot()
	// 			.HAlign(HAlign_Center)
	// 			.AutoHeight()
	// 			[
	// 				Locals::MakeButton(LOCTEXT("DownButtonLabel", "Down"), FVector(0, 0, -Factor))
	// 			]
	//
	// 	];

	SAssignNew(ToolkitWidget, SBorder)
		.HAlign(HAlign_Center)
		.Padding(25)
		//.IsEnabled_Static(&Locals::IsWidgetEnabled)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.MaxHeight(24)
			[
				SNew(SButton)
				.Text(FText::FromString("Select All NPC's"))
				.OnClicked_Lambda([]()
				{
					if (GEngine && GEditor)
					{
						TArray<AQuestGiverActor*> QuestGiversArray;
						for	(auto Iter = GEditor->GetSelectedActorIterator(); Iter; ++Iter)
						{
							if (auto QuestGiver = Cast<AQuestGiverActor>(*Iter))
							{
								QuestGiversArray.Add(QuestGiver);
							}
						}
						GEditor->SelectNone(true, true);
						if (QuestGiversArray.Num() == 0)
						{
							auto Subsystem  = GEditor->GetEditorSubsystem<UNPCEditorSubsystem>();
							if (Subsystem)
							{
								QuestGiversArray =  Subsystem->GetQuestGiverActors();
							}
							for (auto QuestGiver : QuestGiversArray)
							{
								GEditor->SelectActor(QuestGiver, true, true);
							}
						}
						else
						{
							TArray<AActor*>QuestObjectivesArray; 
							TArray<AActor*>QuestsArray;
							for (auto QuestGiver : QuestGiversArray)
							{
								QuestGiver->GetAttachedActors(QuestsArray);
								for (auto Actor : QuestsArray)
								{
									if (auto Quest = Cast<AQuestActor>(Actor) )
									{
										auto Objectives = Quest->GetObjectives();
										for	(auto Objective : Objectives)
										{
											if (auto InteractionObjective = Cast<UInteractionObjective>(Objective))
											{
												QuestObjectivesArray.Add(InteractionObjective->Target);
											}
											else if (auto LocationObjective = Cast<ULocationObjective>(Objective))
											{
												QuestObjectivesArray.Add(LocationObjective->Marker);
											}
											else if (auto CollectionObjective = Cast<UCollectionObjective>(Objective))
											{
												auto Subsystem  = GEditor->GetEditorSubsystem<UNPCEditorSubsystem>();
												if (Subsystem)
												{
													//Subsystem->FindActorsOfClass(CollectionObjective->GetClass());
													for (auto CollectableActor : Subsystem->FindActorsOfClass(CollectionObjective->GetClass()))
													{
														QuestObjectivesArray.Add(CollectableActor);
													}
												}
											}
										}
									}
								}
							}
							for (auto QuestObjective : QuestObjectivesArray)
							{
								GEditor->SelectActor(QuestObjective, true, true);
							}
						}
						
					}
					return FReply::Handled();
				})

				
			]
		];	
		
	FModeToolkit::Init(InitToolkitHost);
}

FName FQuestEditorModeEdModeToolkit::GetToolkitFName() const
{
	return FName("QuestEditorModeEdMode");
}

FText FQuestEditorModeEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("QuestEditorModeEdModeToolkit", "DisplayName", "QuestEditorModeEdMode Tool");
}

class FEdMode* FQuestEditorModeEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FQuestEditorModeEdMode::EM_QuestEditorModeEdModeId);
}

#undef LOCTEXT_NAMESPACE
