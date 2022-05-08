#include "Audio/DialogueVoiceList.h"
#include "Core/Log.h"

/**
 * @brief Get a random audio file from the array of available audio files
 * @return A random audio file from the array of available audio files
 */
USoundBase* UDialogueVoiceList::GetRandomVoice()
{
	const int Index = FMath::RandRange(0, Voices.Num() - 1);
	ULog::Info("DialogueVoiceList::GetRandomVoice", FString("Index = ").Append(FString::FromInt(Index)));
	return Voices[Index];
}