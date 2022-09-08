<p align="center">
<img src="logo/logo-big.png" width=50%>
</p>

## About AudioPlusPlus
AudioPlusPlus (A++) is an early development audio playback library designed for easy integration with any programs.

A++ is currently in very early development stages. Please consider helping by checking out the roadmap here - https://trello.com/b/67YcKpif/audioplusplus

## How to build
AudioPlusPlus can be built using CMake through the following steps.
1. Clone this repository to your machine using `git clone https://github.com/callumc34/AudioPlusPlus` and move into the directory `cd AudioPlusPlus`
2. Setup the build directory
```bash
mkdir build
cd build
```
3. Install the dependencies for this project:

### Windows
The preferred way to install dependencies on Windows is using [Microsoft's VCPKG](https://github.com/microsoft/vcpkg) manager.

When running the following command, vcpkg will automatically install all the required dependencies.
```bash
cmake .. --toolchain [path to vcpkg]/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=[architecture-platform-static/dynamic(leave blank)]
```

### Linux
For linux the majority of these packages can be installed using the package manager
```bash
sudo apt install libasound2-dev libflac-dev libogg-dev libtool libvorbis-dev libopus-dev libmp3lame-dev libmpg123-dev libtag1-dev
```

##### Note: These packages may be out of date and not provide full functionality - see alternative for a better option.

### Alternative
Some of the packages installed using the linux package manager may be out of date or lack full functionality.

It is recommended on linux that you manually build both portaudio and sndfile.

The program will output the urls of all the packages so that you can build them yourself.

##### Note: CMake on windows can have trouble finding the installed packages - use the option `-DDEPENDENCIES_ROOT=[Path to install location of dependencies]` to aid CMake in finding them.

4. Build the project
```bash
cmake --build .
cmake --install .
```

## CMake Options - NOTE: Not all functionality is added yet
You can pass additional options with `-D<parameter>=<value>` when you run
`cmake` command. Some useful system options:
##### Finding dependency options
If you built your own dependencies and installed them using `cmake --install` on windows the best way to let CMake find the packages is with the following variables
- `DEPENDENCIES_ROOT` - Install location of the following packages. On linux if the packages were installed to the default prefix CMake should be able to find them without the need for any variables.

Or specify where to find each package individually
- `FLAC_ROOT` - Install location of FLAC Package
- `LAME_ROOT` - Install location of LAME files with structure `/include` and `/lib`
- `MPG123_ROOT` - Install location of MPG123 Package
- `OGG_ROOT` - Install location of OGG Package
- `OPUS_ROOT` - Install location of OPUS package
- `PORTAUDIO_ROOT` - Install location of PortAudio package
- `SNDFILE_ROOT` - Install location of libsndfile package
- `SPDLOG_ROOT` - Install location of spdlog package
- `Vorbis_ROOT` - Install location of vorbis package
- `TAGLIB_ROOT` - Install location of Taglib package

##### Other options
- `BUILD_EXAMPLES` - Builds the example programs
- `ENABLE_PACKAGE_CONFIG` - Generate and install [package config file](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#config-file-packages).
- `INSTALL_PKGCONFIG_MODULE` - Generate and install [pkg-config module](https://people.freedesktop.org/~dbn/pkg-config-guide.html).
- `BUILD_WITH_LOGGING` - Build with logging support (requires SpdLog)
- `CMAKE_INSTALL_PREFIX` - build install location, the same as `--prefix` option
  of `configure` script
- `ENABLE_STATIC_RUNTIME` - enable static runtime on Windows platform (MSVC and
  MinGW), `OFF` by default.
- `BUILD_DOCUMENTATION` - Builds the doxygen documentation,

## Examples
Check out the examples folder for how to integrate into your app.