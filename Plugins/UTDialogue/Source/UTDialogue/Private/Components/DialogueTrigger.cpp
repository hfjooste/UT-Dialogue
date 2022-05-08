#include "Components/DialogueTrigger.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Core/DialogueManager.h"
#include "Core/Log.h"

/**
 * @brief Begins Play for the component
 */
void UDialogueTrigger::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner == nullptr)
	{
		ULog::Error("DialogueTrigger::BeginPlay", "Owner is nullptr");
		return;
	}

	ULog::Info("DialogueTrigger::BeginPlay", "Binding to overlap events");
	Owner->OnActorBeginOverlap.AddDynamic(this, &UDialogueTrigger::OnActorBeginOverlap);
	Owner->OnActorEndOverlap.AddDynamic(this, &UDialogueTrigger::OnActorEndOverlap);
}

/**
 * @brief Show the dialogue widget using the provided information
 */
void UDialogueTrigger::ShowDialogue()
{
	UDialogueWidget* DialogueWidget = GetDialogueWidget();
	if (DialogueWidget == nullptr)
	{
		ULog::Error("DialogueTrigger::ShowDialogue", "Dialogue widget is nullptr");
		return;
	}

	DialogueWidget->Show(DialogueTitles, DialogueMessages, DialogueVoices);
}

/**
 * @brief Show the dialogue interact widget using the provided information
 */
void UDialogueTrigger::ShowInteractWidget()
{
	UDialogueInteractWidget* InteractWidget = GetInteractWidget();
	if (InteractWidget == nullptr)
	{
		ULog::Error("DialogueTrigger::ShowInteractWidget", "Interact widget is nullptr");
		return;
	}

	InteractWidget->ShowWidget(InteractBeforeText, InteractAfterText, InputIndicatorWidgetClass);
}

/**
 * @brief Hide the dialogue interact widget
 */
void UDialogueTrigger::HideInteractWidget()
{
	UDialogueInteractWidget* InteractWidget = GetInteractWidget();
	if (InteractWidget == nullptr)
	{
		ULog::Error("DialogueTrigger::HideInteractWidget", "Interact widget is nullptr");
		return;
	}

	InteractWidget->HideWidget(true);
}

/**
 * @brief Called when another actor begins to overlap the parent actor
 * @param OverlappedActor The actor that triggered the overlap event
 * @param OtherActor The actor responsible for triggering the overlap event
 */
void UDialogueTrigger::OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == nullptr)
	{
		ULog::Error("DialogueTrigger::OnActorBeginOverlap", "OtherActor is nullptr");
		return;
	}

	if (!OtherActor->IsA(PlayerClass))
	{
		ULog::Info("DialogueTrigger::OnActorBeginOverlap", "OtherActor is not the player");
		return;
	}
	
	ADialogueManager* DialogueManager = dynamic_cast<ADialogueManager*>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ADialogueManager::StaticClass()));
	if (DialogueManager == nullptr)
	{
		ULog::Error("DialogueTrigger::OnActorBeginOverlap", "DialogueManager is nullptr");
		return;
	}

	ULog::Trace("DialogueTrigger::OnActorBeginOverlap", "Showing the interact widget");
	DialogueManager->SetCurrentDialogueTrigger(this);
	ShowInteractWidget();
}

/**
 * @brief Called when another actor stops overlapping the parent actor
 * @param OverlappedActor The actor that triggered the overlap event
 * @param OtherActor The actor responsible for triggering the overlap event
 */
void UDialogueTrigger::OnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == nullptr)
	{
		ULog::Error("DialogueTrigger::OnActorEndOverlap", "OtherActor is nullptr");
		return;
	}

	if (!OtherActor->IsA(PlayerClass))
	{
		ULog::Info("DialogueTrigger::OnActorEndOverlap", "OtherActor is not the player");
		return;
	}

	ADialogueManager* DialogueManager = dynamic_cast<ADialogueManager*>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ADialogueManager::StaticClass()));
	if (DialogueManager == nullptr)
	{
		ULog::Error("DialogueTrigger::OnActorEndOverlap", "DialogueManager is nullptr");
		return;
	}

	ULog::Trace("DialogueTrigger::OnActorEndOverlap", "Hiding the interact widget");
	DialogueManager->ResetDialogueTrigger(this);
	HideInteractWidget();
}

/**
 * @brief Get a reference to the interact widget
 * @return A reference to the interact widget
 */
UDialogueInteractWidget* UDialogueTrigger::GetInteractWidget() const
{
	TArray<UUserWidget*> InteractWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), InteractWidgets, UDialogueInteractWidget::StaticClass(), false);

	for (UUserWidget* Widget : InteractWidgets)
	{
		UDialogueInteractWidget* InteractWidget = dynamic_cast<UDialogueInteractWidget*>(Widget);
		if (InteractWidget != nullptr)
		{
			return InteractWidget;
		}

		ULog::Warning("DialogueTrigger::GetInteractWidget", "Dynamic cast failed");
	}

	return nullptr;
}

/**
 * @brief Get a reference to the dialogue widget 
 * @return A reference to the dialogue widget
 */
UDialogueWidget* UDialogueTrigger::GetDialogueWidget() const
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