#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogueVoiceList.generated.h"

/**
 * @brief Contains an array of voice files that can be played when a dialogue is shown
 */
UCLASS(Blueprintable, BlueprintType)
class UTDIALOGUE_API UDialogueVoiceList final : public UDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * @brief An array of audio files that can be played
	 */
	UPROPERTY(EditAnywhere, Category = "NPC Voice")
	TArray<USoundBase*> Voices;

	/**
	 * @brief Get a random audio file from the array of available audio files
	 * @return A random audio file from the array of available audio files
	 */
	UFUNCTION(BlueprintCallable, Category = "Unreal Toolbox|Dialogue")
	USoundBase* GetRandomVoice();
};