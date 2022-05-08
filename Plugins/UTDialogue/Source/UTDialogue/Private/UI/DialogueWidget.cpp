#include "UI/DialogueWidget.h"
#include "Components/AudioComponent.h"
#include "Components/TextBlock.h"
#include "Core/DialogueManager.h"
#include "Kismet/GameplayStatics.h"
#include "Core/Log.h"

/**
 * @brief Overridable native event for when the widget has been constructed
 */
void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Collapsed);
}

/**
 * @brief Function called every frame on this widget
 * @param MyGeometry Represents the position, size, and absolute position of a the widget
 * @param InDeltaTime he time since the last tick
 */
void UDialogueWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		if (IsAudioPlaying())
		{
			ULog::Info("DialogueWidget::NativeTick", "Stopping audio");
			AudioComponent->Stop();
		}
		
		return;
	}
	
	if (!BusyTyping)
	{
		return;
	}

	if (!IsAudioPlaying())
	{
		ULog::Trace("DialogueWidget::NativeTick", "Playing audio");
		AudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), Voices[Index].GetDefaultObject()->GetRandomVoice());
		AudioComponent->Play();
	}

	TypingCounter += InDeltaTime;
	if (TypingCounter <= 0.05f)
	{
		return;
	}

	TypingIndex++;
	TypingCounter = 0;

	const FString CurrentMessage = Messages[Index].ToString();
	if (TypingIndex >= CurrentMessage.Len())
	{
		StopTyping();
		return;
	}

	MessageText->SetText(FText::FromString(CurrentMessage.Left(TypingIndex)));
}

/**
 * @brief Show the Dialogue Widget by using the specified information
 * @param NewTitles The array of titles to display
 * @param NewMessages The array of messages to display
 * @param NewVoices The array of voice files to play
 */
void UDialogueWidget::Show(const TArray<FText> NewTitles, const TArray<FText> NewMessages,
	const TArray<TSubclassOf<UDialogueVoiceList>> NewVoices)
{
	if (NewTitles.Num() != NewMessages.Num() || NewTitles.Num() != NewVoices.Num())
	{
		ULog::Error("DialogueWidget::Show", "Invalid dialogue data provided");
		return;
	}

	ULog::Info("DialogueWidget::Show", "Showing dialogue");
	
	Titles = NewTitles;
	Messages = NewMessages;
	Voices = NewVoices;
	UpdateIndex(0);
	SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::PlaySound2D(GetWorld(), InteractSound);
}

/**
 * @brief Skip the type animation or continue to the next message in the list
 * @return A boolean value indicating if the last message was skipped
 */
bool UDialogueWidget::SkipMessage()
{
	ULog::Trace("DialogueWidget::SkipMessage", "Skipping message");
	UGameplayStatics::PlaySound2D(GetWorld(), InteractSound);
	
	if (BusyTyping)
	{
		StopTyping();
		return false;
	}

	if (Index + 1 >= Titles.Num())
	{
		ADialogueManager* DialogueManager = dynamic_cast<ADialogueManager*>(
			UGameplayStatics::GetActorOfClass(GetWorld(), ADialogueManager::StaticClass()));
		if (DialogueManager == nullptr)
		{
			ULog::Error("DialogueTrigger::OnActorBeginOverlap", "DialogueManager is nullptr");
		}
		else
		{
			DialogueManager->OnDialogueDismissed();
		}
		
		ULog::Info("DialogueWidget::SkipMessage", "Hiding dialogue widget");
		SetVisibility(ESlateVisibility::Collapsed);
		
		if (IsAudioPlaying())
		{
			ULog::Info("DialogueWidget::SkipMessage", "Stopping audio");
			AudioComponent->Stop();
			AudioComponent = nullptr;
		}
		
		return true;
	}
	
	UpdateIndex(Index + 1);
	return false;
}

/**
 * @brief Update the character index in the typing animation
 * @param NewIndex The new character index
 */
void UDialogueWidget::UpdateIndex(const int NewIndex)
{
	ULog::Info("DialogueWidget::UpdateIndex", FString("NewIndex = ").Append(FString::FromInt(NewIndex)));
	Index = NewIndex;
	TitleText->SetText(Titles[Index]);
	MessageText->SetText(FText::GetEmpty());
	BusyTyping = true;
}

/**
 * @brief Stop the typing animation and display the full message
 */
void UDialogueWidget::StopTyping()
{
	ULog::Trace("DialogueWidget::StopTyping", "Stopping to type");
	BusyTyping = false;
	TypingIndex = 0;
	TypingCounter = 0;
	MessageText->SetText(Messages[Index]);
}

/**
 * @brief Check if a voice file is playing
 * @return A boolean value indicating if a voice file is playing
 */
bool UDialogueWidget::IsAudioPlaying() const
{
	return AudioComponent != nullptr && AudioComponent->IsPlaying();
}