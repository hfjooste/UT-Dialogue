# Dialogue Plugin
A system used to manage interact widgets, dialogues and voice files

## Installation
1. Download the latest release from GitHub
2. Navigate to `C:\Program Files\Epic Games\UE_{VERSION}\Engine\Plugins\`
3. Create a `Marketplace` folder if needed
4. Extract the release and copy to the `Marketplace` folder
5. Open Unreal Engine
6. Click on `Edit > Plugins`
7. Enable the plugin under the `Installed > Unreal Toolbox` category
8. Restart Unreal Engine

## Dialogue Voice List
The `Dialogue Voice List` contains a list of audio files that is played when a dialogue is shown. A random audio file is selected whenever needed. The following properties and functions can be used:
1. `Voices` - An array of audio files that can be played
2. `Get Random Voice` - Return a random audio file from the array of available audio files

## Dialogue Interact Widget
The `Dialogue Interact Widget` is a simple UI widget that displays some text and an `Input Indicator Widget`. This widget is used when the player enters the `Dialogue Trigger`. The following UI elements are required when creating a `Dialogue Interact Widget`:
1. `Container` - A `Horizontal Box` that contains all the elements of the widget
2. `Before Text` - A `Text Block` that is used to display the start of the interact text
3. `After Text` - A `Text Block` that is used to display the end of the interact text

You also need to set up the following animations:
1. `Show Animation` - An animation that is played when the `Dialogue Interact Widget` is shown
2. `Hide Animation` - An animation that is played when the `Dialogue Interact Widget` is dismissed

The following functions can be used to interact with the `Dialogue Interact Widget`:
1. `Show Widget` - Show the `Dialogue Interact Widget` by using the specified information
2. `Hide Widget` - Hide the `Dialogue Interact Widget` by either playing the hide animation or by just setting the visibility

## Dialogue Widget
The `Dialogue Widget` is a simple UI widget that displays a title and message text. The following UI elements are required when creating a `Dialogue Widget`:
1. `Title Text` - A `Text Block` that is used to display the title of the dialogue
2. `Message Text` - A `Text Block` that is used to display the message of the dialogue

You should also set the following properties before using the `Dialogue Widget`:
1. `Interact Sound` - A `Sound Base` that is played when showing the widget or when skipping a message

You can interact with the `Dialogue Widget` by using the following functions:
1. `Show` - Show the `Dialogue Widget` by using the specified information
2. `Skip Message` - Skip the type animation or continue to the next message in the list

## Dialogue Trigger
A `Dialogue Trigger` can be added to any actor that the player can interact with. The `Dialogue Trigger` contains all the information for the interaction. Before you can use the `Dialogue Trigger`, you need to set the following properties:
1. `Player Class` - A reference to the player class. This is used to check if the player is entering the trigger
2. `Input Indicator Class` - A reference to the `Input Indicator Widget` class that will be used whn entering this trigger
3. `Interact Before Text` - The text displayed at the start of the `Dialogue Interact Widget`
4. `Interact After Text` - The text displayed at the end of the `Dialogue Interact Widget`
5. `Dialogue Titles` - An array of titles displayed in the `Dialogue Widget` after interacting with this trigger
6. `Dialogue Messages` - An array of messages displayed in the `Dialogue Widget` after interacting with this trigger
7. `Dialogue Voices` - An array of `Dialogue Voice List` items used by the `Dialogue Widget` after interacting with this trigger

After setting up the trigger, you can use the following functions:
1. `Show Dialogue` - Show the `Dialogue Widget` using the provided information
2. `Show Interact Widget` - Show the `Dialogue Interact Widget` using the provided information
3. `Hide Interact Widget` - Hide the `Dialogue Interact Widget`

## Dialogue Manager
The `Dialogue Manager` is used to manage all the triggers and widgets. This actor needs to be placed in every map where you use the dialogue system. The following functions is available:
1. `Is Dialogue Shown` - Return a boolean value indicating if the `Dialogue Widget` is currently shown
2. `Set Current Dialogue Trigger` - Set the `Dialogue Trigger` that the player is currently inside
3. `Reset Dialogue Trigger` - Reset the `Dialogue Trigger` after the player leaves the trigger
4. `Show Interact Widget` - Show the `Dialogue Interact Widget` using the information specified by the current `Dialogue Trigger`
5. `Show Dialogue` - Show the `Dialogue Widget` using the information specified by the current `Dialogue Trigger`
6. `Skip Dialogue Message` - Skip the current message in the `Dialogue Widget`
7. `On Dialogue Dismissed` - Clean up the UI after the `Dialogue Widget` is dismissed