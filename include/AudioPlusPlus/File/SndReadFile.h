#pragma once
#include <AudioPlusPlus/File/ReadFile.h>
#include <sndfile.hh>

namespace AudioPlusPlus
{
    /**
     * @brief      Class to read audio from a file using libsndfile.
     */
    class SndReadFile : public IReadFile, private SndfileHandle
    {
        public:
            /**
             * @brief      Constructs a new ReadFile using SndFile's SndfileHandle audio file IO class.
             *
             * @param[in]  path  The path to the file.
             */
            SndReadFile(const std::string& path);

            /**
             * @brief      Destructor for a SndReadFile object.
             */
            ~SndReadFile();
            
            double GetPosition();
            int Close();

        private:
            /** Whether the file is closed */
            bool closed = false;

            int ReadToBuffer(
                const void* inputBuffer, void* outputBuffer,
                unsigned long framesPerBuffer,
                const PaStreamCallbackTimeInfo* timeInfo,
                PaStreamCallbackFlags statusFlags,
                void* userData
            );
    };
}