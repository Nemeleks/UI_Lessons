// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseToolEditorCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"

void FBaseToolEditorCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TSet<UClass*> Classes;

	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);

	for (auto WeakObject : ObjectsBeingCustomized)
	{
		if (UObject* Instance  = WeakObject.Get())
		{
			Classes.Add(Instance->GetClass());
		}
	}

	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Commands");

	for (UClass* Class : Classes)
	{
		for	(TFieldIterator<UFunction> FuncIt(Class); FuncIt; ++FuncIt)
		{
			UFunction* Function = *FuncIt;
			if (Function->HasAnyFunctionFlags(FUNC_Exec) && (Function->NumParms == 0))
			{
				const FString FunctionName = Function->GetName();
				const FText ButtonCaption = FText::FromString(FunctionName);
				const FText FilterString = FText::FromString(FunctionName);;

				Category.AddCustomRow(FilterString)
				.ValueContent()
				[
					SNew(SButton)
					.Text(ButtonCaption)
					.OnClicked(FOnClicked::CreateStatic(&FBaseToolEditorCustomization::ExecuteToolCommand, &DetailBuilder, Function))
				];
			}
		}
	}
}

TSharedRef<IDetailCustomization> FBaseToolEditorCustomization::MakeInstance()
{
	return MakeShareable(new FBaseToolEditorCustomization);
}

FReply FBaseToolEditorCustomization::ExecuteToolCommand(IDetailLayoutBuilder* DetailBuilder, UFunction* MethodToExecute)
{
	return  FReply::Handled();
}
