#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "UI/InputIndicatorWidget.h"
#include "DialogueInteractWidget.generated.h"

/**
 * @brief A widget that is displayed when the player enters the dialogue trigger
 */
UCLASS()
class UTDIALOGUE_API UDialogueInteractWidget final : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief An animation that is played when the dialogue interact widget is shown
	 */
	UPROPERTY(meta = (BindWidgetAnim), Transient, EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UWidgetAnimation* ShowAnimation;

	/**
	 * @brief An animation that is played when the dialogue interact widget is shown
	 */
	UPROPERTY(meta = (BindWidgetAnim), Transient, EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UWidgetAnimation* HideAnimation;
	
	/**
	 * @brief A horizontal box that contains all the elements of the widget
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UHorizontalBox* Container;
	
	/**
	 * @brief A text block that is used to display the start of the interact text
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UTextBlock* BeforeText;

	/**
	 * @brief A text block that is used to display the end of the interact text
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UTextBlock* AfterText;

	/**
	 * @brief Show the dialogue interact widget by using the specified information
	 * @param Before The text that is displayed at the start of the widget
	 * @param After The text that is displayed at the end of the widget
	 * @param InputIndicatorClass The input indicator class that is displayed in the widget
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	void ShowWidget(FText Before, FText After, TSubclassOf<UInputIndicatorWidget> InputIndicatorClass);

	/**
	 * @brief Hide the dialogue interact widget by either playing the hide animation or by just setting the visibility
	 * @param Animated Should the animation be played?
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	void HideWidget(bool Animated);

protected:
	/**
	 * @brief Overridable native event for when the widget has been constructed
	 */
	virtual void NativeConstruct() override;
	
private:
	/**
	 * @brief The input indicator class that is displayed in the widget
	 */
	UPROPERTY()
	UInputIndicatorWidget* InputIndicator;
	
	/**
	 * @brief Initialize the widget by setting the text and input indicator
	 * @param Before The text that is displayed at the start of the widget
	 * @param After The text that is displayed at the end of the widget
	 * @param InputIndicatorClass The input indicator class that is displayed in the widget
	 */
	void InitializeWidget(FText Before, FText After, TSubclassOf<UInputIndicatorWidget> InputIndicatorClass);
	
	/**
	 * @brief Initialize the input indicator that is displayed in the widget
	 * @param InputIndicatorClass The input indicator class that is displayed in the widget
	 */
	void InitializeInputIndicator(TSubclassOf<UInputIndicatorWidget> InputIndicatorClass);
};