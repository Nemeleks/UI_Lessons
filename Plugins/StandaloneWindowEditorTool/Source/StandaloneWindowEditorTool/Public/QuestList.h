// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "QuestList.generated.h"

/**
 * 
 */

class AQuestActor;

class SQuestList : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS( SQuestList ){}
	SLATE_END_ARGS()

	/**
    	 * Constructs this widget
    	 *
    	 * @param InArgs    Declaration from which to construct the widget
    	 */
    	void Construct(const FArguments& InArgs);
    
    	/** SModuleUI destructor */
    	~SQuestList();
    	
    	private:
        	struct FQuestListItem
        	{
        		FText QuestName;
        		FText QuestDescription;
        		bool bIsStoryQuest;
        		bool bKeepObjectivesOrder;
        		AQuestActor* PreviousQuest;
        		AQuestActor* QuestPtr;
        	};

	TSharedRef<ITableRow> OnGenerateWidgetForModuleListView(TSharedPtr< FQuestListItem > InItem, const TSharedRef<STableViewBase>& OwnerTable);

	/**
	 * Called by the engine's module manager when a module is loaded, unloaded, or the list of known
	 * modules has changed
	 */
	void OnModulesChanged( FName ModuleThatChanged, EModuleChangeReason ReasonForChange );

	/**
	 * Updates our module list items
	 */
	void UpdateModuleListItems();

	/**
	 *  module list item filter 
	 */
	void OnFilterTextChanged(const FText& InFilterText);

	FReply OnButtonPressed();
	TArray<AQuestActor> Quests;

	//TSharedPtr<FQuestListItem> Item;

	void EditQuestPressed();

private:

	typedef SListView< TSharedPtr< FQuestListItem > > SQuestListView;
	typedef TArray< TSharedPtr< FQuestListItem > > FQuestArray;

	/** List items for the module list */
	TArray< TSharedPtr< FQuestListItem > > QuestListItems;

	/** List of all known modules */
	TSharedPtr< SQuestListView > QuestListView;
};
