#pragma once
// Devices
#include <AudioPlusPlus/Device/DeviceManager.h>

// Exceptions
#include <AudioPlusPlus/Exceptions/Exception.h>

// Log
#include <AudioPlusPlus/Log/Log.h>

// Player
#include <AudioPlusPlus/Player/Player.h>

// Recorder
#include <AudioPlusPlus/Recorder/Recorder.h>

// Streams
#include <AudioPlusPlus/Stream/StreamManager.h>

// Tagging
#include <AudioPlusPlus/TagHandle/TagHandle.h>

/**
 * Namespace for all AudioPlusPlus objects.
 */
namespace AudioPlusPlus
{
	/**
	 * @brief      Initializes AudioPlusPlus.
	 *
	 * @return     Error code.
	 */
	int Init();

	/**
	 * @brief      Allows the thread to sleep for a much more precise time than sleep().
	 *
	 * Used to allow audio to continue playing when there is no code to execute.
	 * 
	 * @param[in]  seconds  The seconds to sleep for.
	 */
	void Wait(double seconds);

	/**
	 * @brief      Exit AudioPlusPlus.
	 *
	 * @return     Error code.
	 */
	int Exit();
}