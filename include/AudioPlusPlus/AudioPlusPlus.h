#pragma once
//Devices
#include <AudioPlusPlus/Device/DeviceManager.h>

//Files
#include <AudioPlusPlus/File/ReadFile.h>
#include <AudioPlusPlus/File/WriteFile.h>

//Log
#include <AudioPlusPlus/Log/Log.h>

//Player
#include <AudioPlusPlus/Player/Player.h>

//Recorder
#include <AudioPlusPlus/Recorder/Recorder.h>

//Streams
#include <AudioPlusPlus/Stream/StreamManager.h>

//Tagging
#include <AudioPlusPlus/TagHandle/TagHandle.h>

namespace AudioPlusPlus
{
	int Init();
	int Exit();
}