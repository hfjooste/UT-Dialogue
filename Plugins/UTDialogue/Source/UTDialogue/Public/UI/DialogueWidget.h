#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Audio/DialogueVoiceList.h"
#include "DialogueWidget.generated.h"

/**
 * @brief A widget that is displays the dialogue entry's title and text
 */
UCLASS()
class UTDIALOGUE_API UDialogueWidget final : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief Used to display the title of the dialogue
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UTextBlock* TitleText;

	/**
	 * @brief Used to display the message of the dialogue
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UTextBlock* MessageText;

	/**
	 * @brief Sound that is played when showing the widget or when skipping a message
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	USoundBase* InteractSound;

	/**
	 * @brief Show the Dialogue Widget by using the specified information
	 * @param NewTitles The array of titles to display
	 * @param NewMessages The array of messages to display
	 * @param NewVoices The array of voice files to play
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	void Show(TArray<FText> NewTitles, TArray<FText> NewMessages, TArray<TSubclassOf<UDialogueVoiceList>> NewVoices);

	/**
	 * @brief Skip the type animation or continue to the next message in the list
	 * @return A boolean value indicating if the last message was skipped
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	bool SkipMessage();

protected:
	/**
	 * @brief Overridable native event for when the widget has been constructed
	 */
	virtual void NativeConstruct() override;
	
	/**
	 * @brief Function called every frame on this widget
	 * @param MyGeometry Represents the position, size, and absolute position of a the widget
	 * @param InDeltaTime he time since the last tick
	 */
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:	
	/**
	 * @brief The index of the current dialogue entry 
	 */
	int Index;
	
	/**
	 * @brief The array of titles to display
	 */
	TArray<FText> Titles;
	
	/**
	 * @brief The array of messages to display
	 */
	TArray<FText> Messages;
	
	/**
	 * @brief The array of voice files to play
	 */
	UPROPERTY()
	TArray<TSubclassOf<UDialogueVoiceList>> Voices;
	
	/**
	 * @brief The audio component responsible for playing the voice files
	 */
	UPROPERTY()
	UAudioComponent* AudioComponent;
	
	/**
	 * @brief Boolean value indicating if we're busy typing the current dialogue message
	 */
	bool BusyTyping;

	/**
	 * @brief Counter used to slow down the typing animation 
	 */
	float TypingCounter;

	/**
	 * @brief The current character index in the typing animation 
	 */
	int TypingIndex;

	/**
	 * @brief Update the character index in the typing animation
	 * @param NewIndex The new character index
	 */
	void UpdateIndex(int NewIndex);
	
	/**
	 * @brief Stop the typing animation and display the full message
	 */
	void StopTyping();
	
	/**
	 * @brief Check if a voice file is playing
	 * @return A boolean value indicating if a voice file is playing
	 */
	bool IsAudioPlaying() const;
};