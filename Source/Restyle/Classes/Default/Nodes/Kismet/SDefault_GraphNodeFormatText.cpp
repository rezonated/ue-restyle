// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_GraphNodeFormatText.h"
#include "Widgets/SBoxPanel.h"
#include "GraphEditorSettings.h"
#include "K2Node_FormatText.h"
#include "NodeFactory.h"


//////////////////////////////////////////////////////////////////////////
// SGraphNodeFormatText

void SDefault_GraphNodeFormatText::Construct(const FArguments& InArgs, UK2Node_FormatText* InNode)
{
	SDefault_GraphNodeK2Default::Construct(SDefault_GraphNodeK2Default::FArguments(), InNode);
}

void SDefault_GraphNodeFormatText::CreatePinWidgets()
{
	// Create Pin widgets for each of the pins, except for the default pin
	for (auto PinIt = GraphNode->Pins.CreateConstIterator(); PinIt; ++PinIt)
	{
		UEdGraphPin* CurrentPin = *PinIt;
		if ((!CurrentPin->bHidden))
		{
			TSharedPtr<SGraphPin> NewPin = FNodeFactory::CreatePinWidget(CurrentPin);
			check(NewPin.IsValid());

			this->AddPin(NewPin.ToSharedRef());
		}
	}
}

void SDefault_GraphNodeFormatText::CreateInputSideAddButton(TSharedPtr<SVerticalBox> InputBox)
{
	TSharedRef<SWidget> AddPinButton = AddPinButtonContent(
		NSLOCTEXT("FormatTextNode", "FormatTextNodeAddPinButton", "Add pin"),
		NSLOCTEXT("FormatTextNode", "FormatTextNodeAddPinButton_Tooltip", "Adds an argument to the node"),
		false);

	FMargin AddPinPadding = Settings->GetInputPinPadding();
	AddPinPadding.Top += 6.0f;

	InputBox->AddSlot()
		.AutoHeight()
		.VAlign(VAlign_Center)
		.Padding(AddPinPadding)
		[
			AddPinButton
		];
}

EVisibility SDefault_GraphNodeFormatText::IsAddPinButtonVisible() const
{
	EVisibility VisibilityState = EVisibility::Collapsed;
	if (NULL != Cast<UK2Node_FormatText>(GraphNode))
	{
		VisibilityState = SGraphNode::IsAddPinButtonVisible();
		if (VisibilityState == EVisibility::Visible)
		{
			UK2Node_FormatText* FormatNode = CastChecked<UK2Node_FormatText>(GraphNode);
			VisibilityState = FormatNode->CanEditArguments() ? EVisibility::Visible : EVisibility::Collapsed;
		}
	}
	return VisibilityState;
}

FReply SDefault_GraphNodeFormatText::OnAddPin()
{
	if (UK2Node_FormatText* FormatText = Cast<UK2Node_FormatText>(GraphNode))
	{
		FormatText->AddArgumentPin();
	}
	return FReply::Handled();
}
