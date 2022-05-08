#include "UI/DialogueInteractWidget.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Core/Log.h"

/**
 * @brief Overridable native event for when the widget has been constructed
 */
void UDialogueInteractWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Collapsed);
}

/**
 * @brief Show the dialogue interact widget by using the specified information
 * @param Before The text that is displayed at the start of the widget
 * @param After The text that is displayed at the end of the widget
 * @param InputIndicatorClass The input indicator class that is displayed in the widget
 */
void UDialogueInteractWidget::ShowWidget(const FText Before, const FText After,
	const TSubclassOf<UInputIndicatorWidget> InputIndicatorClass)
{
	ULog::Trace("DialogueInteractWidget::ShowWidget", "Showing widget");
	InitializeWidget(Before, After, InputIndicatorClass);
	SetVisibility(ESlateVisibility::Visible);
	StopAnimation(HideAnimation);
	PlayAnimation(ShowAnimation);
}

/**
 * @brief Hide the dialogue interact widget by either playing the hide animation or by just setting the visibility
 * @param Animated Should the animation be played?
 */
void UDialogueInteractWidget::HideWidget(const bool Animated)
{
	ULog::Trace("DialogueInteractWidget::HideWidget", "Hiding widget");	
	if (!Animated)
	{
		ULog::Trace("DialogueInteractWidget::HideWidget", "Not animated. Setting visibility");
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	ULog::Trace("DialogueInteractWidget::HideWidget", "Playing hide animation");
	StopAnimation(ShowAnimation);
	PlayAnimation(HideAnimation);
}

/**
 * @brief Initialize the widget by setting the text and input indicator
 * @param Before The text that is displayed at the start of the widget
 * @param After The text that is displayed at the end of the widget
 * @param InputIndicatorClass The input indicator class that is displayed in the widget
 */
void UDialogueInteractWidget::InitializeWidget(const FText Before, const FText After,
                                               const TSubclassOf<UInputIndicatorWidget> InputIndicatorClass)
{
	Super::Initialize();
	ULog::Trace("DialogueInteractWidget::InitializeWidget", "Initializing widget");
	
	BeforeText->SetText(Before);
	AfterText->SetText(After);

	BeforeText->SetVisibility(Before.IsEmpty() ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
	AfterText->SetVisibility(After.IsEmpty() ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);

	InitializeInputIndicator(InputIndicatorClass);	
}

/**
 * @brief Initialize the input indicator that is displayed in the widget
 * @param InputIndicatorClass The input indicator class that is displayed in the widget
 */
void UDialogueInteractWidget::InitializeInputIndicator(const TSubclassOf<UInputIndicatorWidget> InputIndicatorClass)
{
	ULog::Trace("DialogueInteractWidget::InitializeInputIndicator", "Initializing input indicator");
	if (InputIndicatorClass == nullptr)
	{
		ULog::Error("DialogueInteractWidget::InitializeInputIndicator", "Input indicator class not set");
		return;
	}

	if (InputIndicator != nullptr)
	{
		ULog::Trace("DialogueInteractWidget::InitializeInputIndicator", "Removing existing input indicator");
		InputIndicator->RemoveFromViewport();
		InputIndicator->RemoveFromParent();
		InputIndicator = nullptr;
	}

	InputIndicator = CreateWidget<UInputIndicatorWidget>(GetWorld(), InputIndicatorClass);
	InputIndicator->AddToViewport();
	AfterText->RemoveFromParent();
	Container->AddChild(InputIndicator);
    
	UHorizontalBoxSlot* AfterTextSlot = Container->AddChildToHorizontalBox(AfterText);
	AfterTextSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
}