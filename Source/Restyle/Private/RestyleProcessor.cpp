// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "RestyleProcessor.h"

#include "TimerManager.h"

#include "Engine/World.h"

#include "Fonts/SlateFontInfo.h"

#include "Framework/Application/SlateApplication.h"

#include "Layout/Margin.h"

#include "Misc/FileHelper.h"

#include "Styling/SlateBrush.h"
#include "Styling/SlateColor.h"
#include "Styling/SlateStyle.h"
#pragma region Wrapper
namespace FSlateStyleSetWrapper_Data
{
	/** float property storage. */
	static TMap<FName, float> Cached_FloatValues;

	/** FVector2D property storage. */
	static TMap<FName, FVector2f> Cached_Vector2DValues;

	/** Color property storage. */
	static TMap<FName, FLinearColor> Cached_ColorValues;

	/** FSlateColor property storage. */
	static TMap<FName, FSlateColor> Cached_SlateColorValues;

	/** FMargin property storage. */
	static TMap<FName, FMargin> Cached_MarginValues;

	/* FSlateBrush property storage */
	static TMap<FName, FSlateBrush*> Cached_BrushResources;

	/** FSlateFontInfo property storage. */
	static TMap<FName, FSlateFontInfo> Cached_FontInfoResources;

	static bool bCached;
}

class FSlateStyleSetWrapper : public FSlateStyleSet
{
public:
	static void CacheData(FSlateStyleSetWrapper* Set)
	{
		if (!FSlateStyleSetWrapper_Data::bCached) {
			FSlateStyleSetWrapper_Data::bCached = true;
			FSlateStyleSetWrapper_Data::Cached_FloatValues = Set->FloatValues;
			FSlateStyleSetWrapper_Data::Cached_Vector2DValues = Set->Vector2DValues;
			FSlateStyleSetWrapper_Data::Cached_ColorValues = Set->ColorValues;
			FSlateStyleSetWrapper_Data::Cached_SlateColorValues = Set->SlateColorValues;
			FSlateStyleSetWrapper_Data::Cached_MarginValues = Set->MarginValues;
			FSlateStyleSetWrapper_Data::Cached_BrushResources = Set->BrushResources;
			FSlateStyleSetWrapper_Data::Cached_FontInfoResources = Set->FontInfoResources;
		}
	}

	static void RestoreData(FSlateStyleSetWrapper* Set)
	{
		if (ensureMsgf(FSlateStyleSetWrapper_Data::bCached, L"Restyle: Tried to RestoreData, not cached before")) {
			Set->FloatValues = FSlateStyleSetWrapper_Data::Cached_FloatValues;
			Set->Vector2DValues = FSlateStyleSetWrapper_Data::Cached_Vector2DValues;
			Set->ColorValues = FSlateStyleSetWrapper_Data::Cached_ColorValues;
			Set->SlateColorValues = FSlateStyleSetWrapper_Data::Cached_SlateColorValues;
			Set->MarginValues = FSlateStyleSetWrapper_Data::Cached_MarginValues;
			Set->BrushResources = FSlateStyleSetWrapper_Data::Cached_BrushResources;
			Set->FontInfoResources = FSlateStyleSetWrapper_Data::Cached_FontInfoResources;
		}
	}

	static TMap<FName, FSlateBrush*>& GetBrushResources(FSlateStyleSetWrapper* Set) { return Set->BrushResources; }
	static TMap<FName, TSharedRef<FSlateWidgetStyle>>& GetWidgetStyles(FSlateStyleSetWrapper* Set) { return Set->WidgetStyleValues; }
};

#pragma endregion
void FRestyleProcessor::ResetEditorStyle() { FSlateStyleSetWrapper::RestoreData(static_cast<FSlateStyleSetWrapper*>(GetStyle())); }

void FRestyleProcessor::CacheEditorStyle() { FSlateStyleSetWrapper::CacheData(static_cast<FSlateStyleSetWrapper*>(GetStyle())); }

TMap<FName, FSlateBrush*>& FRestyleProcessor::GetBrushResources()
{
	return FSlateStyleSetWrapper::GetBrushResources(static_cast<FSlateStyleSetWrapper*>(GetStyle()));
}

TMap<FName, FSlateBrush*>& FRestyleProcessor::GetCachedBrushResources() { return FSlateStyleSetWrapper_Data::Cached_BrushResources; }

TMap<FName, TSharedRef<FSlateWidgetStyle>>& FRestyleProcessor::GetWidgetStyles()
{
	return FSlateStyleSetWrapper::GetWidgetStyles(static_cast<FSlateStyleSetWrapper*>(GetStyle()));
}

void FRestyleProcessor::ReloadEditorStyle()
{
	if (FSlateApplication::IsInitialized()) { FSlateApplication::Get().GetRenderer()->ReloadTextureResources(); }
}

void FRestyleProcessor::ReloadEditorStyleSafe()
{
	if (GWorld && GWorld->bIsWorldInitialized) {
		GWorld->GetTimerManager().ClearTimer(GlobalReloadHandle);
		GWorld->GetTimerManager().SetTimer(GlobalReloadHandle, [this]() { ReloadEditorStyle(); }, 2, false);
	}
	else { ReloadEditorStyle(); }
}


#undef RootToContentDir
