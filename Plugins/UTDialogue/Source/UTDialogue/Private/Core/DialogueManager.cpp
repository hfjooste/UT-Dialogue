#include "Core/DialogueManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Core/Log.h"

/**
 * @brief Return a boolean value indicating if the dialogue widget is currently shown
 * @return A boolean value indicating if the dialogue widget is currently shown
 */
bool ADialogueManager::IsDialogueShown()
{
	return IsShown;
}

/**
 * @brief Set the dialogue trigger that the player is currently inside
 * @param DialogueTrigger The current dialogue trigger
 */
void ADialogueManager::SetCurrentDialogueTrigger(UDialogueTrigger* DialogueTrigger)
{
	ULog::Info("DialogueManager::SetCurrentDialogueTrigger", "Setting dialogue trigger");
	CurrentDialogueTrigger = DialogueTrigger;
}

/**
 * @brief Reset the dialogue trigger after the player leaves the trigger
 * @param DialogueTrigger The trigger that needs to be reset
 */
void ADialogueManager::ResetDialogueTrigger(const UDialogueTrigger* DialogueTrigger)
{
	if (CurrentDialogueTrigger != DialogueTrigger)
	{
		ULog::Info("DialogueManager::ResetDialogueTrigger", "Reset ignored");
		return;
	}

	ULog::Info("DialogueManager::ResetDialogueTrigger", "Resetting dialogue trigger");
	CurrentDialogueTrigger = nullptr;
}

/**
 * @brief Show the dialogue interact widget using the information specified by the current dialogue trigger
 */
void ADialogueManager::ShowInteractWidget()
{
	if (CurrentDialogueTrigger == nullptr)
	{
		ULog::Error("DialogueManager::ShowInteractWidget", "CurrentDialogueTrigger is nullptr");
		return;
	}

	ULog::Info("DialogueManager::ShowInteractWidget", "Showing interact widget");
	CurrentDialogueTrigger->ShowInteractWidget();
}

/**
 * @brief Show the dialogue widget using the information specified by the current dialogue trigger
 */
void ADialogueManager::ShowDialogue()
{
	if (IsDialogueShown())
	{
		ULog::Warning("DialogueManager::ShowDialogue", "Dialogue is already shown");
		return;
	}
	
	if (CurrentDialogueTrigger == nullptr)
	{
		ULog::Error("DialogueManager::ShowDialogue", "CurrentDialogueTrigger is nullptr");
		return;
	}

	ULog::Info("DialogueManager::ShowDialogue", "Showing dialogue");
	CurrentDialogueTrigger->HideInteractWidget();
	CurrentDialogueTrigger->ShowDialogue();
	IsShown = true;
}

/**
 * @brief Skip the current message in the dialogue widget
 */
void ADialogueManager::SkipDialogueMessage()
{
	if (!IsDialogueShown())
	{
		ULog::Warning("DialogueManager::ShowDialogue", "Dialogue is not shown");
		return;
	}
	
	UDialogueWidget* DialogueWidget = GetDialogueWidget();
	if (DialogueWidget == nullptr)
	{
		ULog::Error("DialogueManager::SkipDialogueMessage", "Dialogue widget is nullptr");
		return;
	}

	DialogueWidget->SkipMessage();
}

/**
 * @brief Clean up the UI after the dialogue widget is dismissed
 */
void ADialogueManager::OnDialogueDismissed()
{
	if (CurrentDialogueTrigger == nullptr)
	{
		ULog::Error("DialogueManager::OnDialogueDismissed", "CurrentDialogueTrigger is nullptr");
		return;
	}
	
	ULog::Info("DialogueManager::OnDialogueDismissed", "Dialogue was dismissed");
	CurrentDialogueTrigger->ShowInteractWidget();
	IsShown = false;
}

/**
 * @brief Get a reference to the dialogue widget 
 * @return A reference to the dialogue widget
 */
UDialogueWidget* ADialogueManager::GetDialogueWidget() const
{
	TArray<UUserWidget*> DialogueWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), DialogueWidgets, UDialogueWidget::StaticClass(), false);

	for (UUserWidget* Widget : DialogueWidgets)
	{
		UDialogueWidget* DialogueWidget = dynamic_cast<UDialogueWidget*>(Widget);
		if (DialogueWidget != nullptr)
		{
			return DialogueWidget;
		}
	}

	ULog::Warning("DialogueTrigger::GetDialogueWidget", "Dynamic cast failed");
	return nullptr;
}