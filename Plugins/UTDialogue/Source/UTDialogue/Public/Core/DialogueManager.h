#pragma once

#include "Components/DialogueTrigger.h"
#include "DialogueManager.generated.h"

/**
 * @brief Used to manage all the dialogue triggers and dialogue widgets
 */
UCLASS()
class UTDIALOGUE_API ADialogueManager final : public AActor
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Return a boolean value indicating if the dialogue widget is currently shown
	 * @return A boolean value indicating if the dialogue widget is currently shown
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	bool IsDialogueShown();
	
	/**
	 * @brief Set the dialogue trigger that the player is currently inside
	 * @param DialogueTrigger The current dialogue trigger
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	void SetCurrentDialogueTrigger(UDialogueTrigger* DialogueTrigger);

	/**
	 * @brief Reset the dialogue trigger after the player leaves the trigger
	 * @param DialogueTrigger The trigger that needs to be reset
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	void ResetDialogueTrigger(const UDialogueTrigger* DialogueTrigger);

	/**
	 * @brief Show the dialogue interact widget using the information specified by the current dialogue trigger
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	void ShowInteractWidget();

	/**
	 * @brief Show the dialogue widget using the information specified by the current dialogue trigger
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	void ShowDialogue();

	/**
	 * @brief Skip the current message in the dialogue widget
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	void SkipDialogueMessage();

	/**
	 * @brief Clean up the UI after the dialogue widget is dismissed
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	void OnDialogueDismissed();

private:
	/**
	 * @brief The dialogue trigger that the player is currently inside
	 */
	UPROPERTY()
	UDialogueTrigger* CurrentDialogueTrigger;

	/**
	 * @brief A boolean value indicating if the dialogue widget is currently shown
	 */
	bool IsShown;

	/**
	 * @brief Get a reference to the dialogue widget 
	 * @return A reference to the dialogue widget
	 */
	UDialogueWidget* GetDialogueWidget() const;
};