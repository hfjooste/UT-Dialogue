#pragma once

#include "Audio/DialogueVoiceList.h"
#include "UI/DialogueInteractWidget.h"
#include "UI/DialogueWidget.h"
#include "DialogueTrigger.generated.h"

/**
 * @brief Contains all the information for a dialogue and handles the interaction
 */
UCLASS(ClassGroup=(Custom), DisplayName="Dialogue Trigger", meta=(BlueprintSpawnableComponent))
class UTDIALOGUE_API UDialogueTrigger final : public UActorComponent
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief A reference to the player class. This is used to check if the player is entering the trigger
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue|Classes")
	TSubclassOf<AActor> PlayerClass;

	/**
	 * @brief A reference to the input indicator widget class that will be used whn entering this trigger
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue|Classes")
	TSubclassOf<UInputIndicatorWidget> InputIndicatorWidgetClass;

	/**
	 * @brief The text displayed at the start of the dialogue interact widget
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue|Interact")
	FText InteractBeforeText;

	/**
	 * @brief The text displayed at the end of the dialogue interact widget
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue|Interact")
	FText InteractAfterText;

	/**
	 * @brief An array of titles displayed in the dialogue widget after interacting with this trigger
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue|Properties")
	TArray<FText> DialogueTitles;

	/**
	 * @brief An array of messages displayed in the dialogue widget after interacting with this trigger
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue|Properties")
	TArray<FText> DialogueMessages;

	/**
	 * @brief An array of dialogue voice list items used by the dialogue widget after interacting with this trigger
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue|Properties")
	TArray<TSubclassOf<UDialogueVoiceList>> DialogueVoices;

	/**
	 * @brief Show the dialogue widget using the provided information
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	void ShowDialogue();

	/**
	 * @brief Show the dialogue interact widget using the provided information
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	void ShowInteractWidget();

	/**
	 * @brief Hide the dialogue interact widget
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	void HideInteractWidget();

protected:
	/**
	 * @brief Begins Play for the component
	 */
	virtual void BeginPlay() override;

private:
	/**
	 * @brief Called when another actor begins to overlap the parent actor
	 * @param OverlappedActor The actor that triggered the overlap event
	 * @param OtherActor The actor responsible for triggering the overlap event
	 */
	UFUNCTION()
	void OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	/**
	 * @brief Called when another actor stops overlapping the parent actor
	 * @param OverlappedActor The actor that triggered the overlap event
	 * @param OtherActor The actor responsible for triggering the overlap event
	 */
	UFUNCTION()
	void OnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	/**
	 * @brief Get a reference to the interact widget
	 * @return A reference to the interact widget
	 */
	UDialogueInteractWidget* GetInteractWidget() const;
	
	/**
	 * @brief Get a reference to the dialogue widget 
	 * @return A reference to the dialogue widget
	 */
	UDialogueWidget* GetDialogueWidget() const;
};