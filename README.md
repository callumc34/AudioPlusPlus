# AudioPlusPlus

<p align="center">
<img src="logo/logo-big.png" width=50%>
</p>

## About AudioPlusPlus
AudioPlusPlus (A++) is an early development audio playback library designed for easy integration with any programs.

A++ is currently in very early development stages. Please consider helping by checking out the roadmap here - https://trello.com/b/67YcKpif/audioplusplus

# How to build
1. Clone this repository to your machine using `git clone --recursive https://github.com/callumc34/AudioPlusPlus`
2. Install the packages either using https://vcpkg.io/en/getting-started.html or `sudo apt install libsndfile1-dev libspdlog-dev portaudio19-dev`
    - Note: Linux currently not supported
3. Build using cmake
#### 3. Note libsndfile should be built with all supported packages to ensure A++ can open as many files as possible.
4. Build spdlog using CMake
5. Open the AudioPlusPlus MSVC solution and build using Visual Studio.

# Examples
Check out the examples folder for how to integrate into your app.
