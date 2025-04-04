// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Widgets/SWidget.h"
#include "Widgets/SOverlay.h"
#include "Engine/GameViewportClient.h"
#include "SDefault_GraphNodeK2Default.h"

class SGraphPin;

class SDefault_GraphNodeK2Event : public SDefault_GraphNodeK2Default
{
public:
	SDefault_GraphNodeK2Event() : SDefault_GraphNodeK2Default(), bHasDelegateOutputPin(false) {}

protected:
	virtual TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle) override;
	virtual bool UseLowDetailNodeTitles() const override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;


	virtual void SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget) override
	{
		TitleAreaWidget = DefaultTitleAreaWidget;
	}

private:
	bool ParentUseLowDetailNodeTitles() const
	{
		return SDefault_GraphNodeK2Event::UseLowDetailNodeTitles();
	}

	EVisibility GetTitleVisibility() const;

	TSharedPtr<SOverlay> TitleAreaWidget;
	bool bHasDelegateOutputPin;
};
