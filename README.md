# AudioPlusPlus

<p align="center">
<img src="logo/logo-big.png" width=50%>
</p>

## About AudioPlusPlus
AudioPlusPlus (A++) is an early development audio playback library designed for easy integration with any programs.

A++ is currently in very early development stages. Please consider helping by checking out the roadmap here - https://trello.com/b/67YcKpif/audioplusplus

## How to build
1. Clone this repository to your machine using `git clone https://github.com/callumc34/AudioPlusPlus`
2. Install the dependencies for this project:
- [Microsoft's VCPKG](https://github.com/microsoft/vcpkg) Can be used to install the dependencies on windows using
```bash
    vcpkg install libogg:x64-windows-static libvorbis:x64-windows-static libflac:x64-windows-static opus:x64-windows-static libogg:x86-windows-static libvorbis:x64-windows-static  libflac:x64-windows-static opus:x64-windows-static mp3lame:x64-windows-static mpg123:x64-windows-static spdlog:x64-windows-static portaudio:x64-windows-static 
```
Similarily for linux the majority of these packages can be installed using the package manager
```bash
sudo apt install libasound2-dev libflac-dev libogg-dev libtool libvorbis-dev libopus-dev libmp3lame-dev libmpg123-dev
```
However for both vcpkg and linux some of these packages are outdated - sndfile and portaudio - and do not have the best features installed.

- It is best to download all the packages and build them individually with full file support for libsndfile (URLs can be located inside the CMakeLists.txt file and will be outputted when attempting to build

3. Then the project can simply be made with cmake
```
mkdir build
cd build
cmake ..
```

CMake will then create the output files
- On Unix this will by default be a makefile which can be ran with
```bash
make
make install
```
- On Windows this will by default be a visual studio solution if the proper tools are installed.

The unified command can then be run to build the files
```
cmake --build
cmake --install
````

## CMake Options - NOTE: Not all functionality is added yet
You can pass additional options with `-D<parameter>=<value>` when you run
`cmake` command. Some useful system options:
##### Finding dependency options
If you built your own dependencies and installed them using `cmake --install` the best way to let CMake find the packages is with the following variables
- `FLAC_ROOT` - Install location of FLAC Package
- `LAME_ROOT` - Install location of LAME files with structure `/include` and `/lib`
- `MPG123_ROOT` - Install location of MPG123 Package
- `OGG_ROOT` - Install location of OGG Package
- `OPUS_ROOT` - Install location of OPUS package
- `PORTAUDIO_ROOT` - Install location of PortAudio package
- `SNDFILE_ROOT` - Install location of libsndfile package
- `SPDLOG_ROOT` - Install location of spdlog package
- `Vorbis_ROOT` - Install location of vorbis package

##### Other options
- `BUILD_SHARED_LIBS` - build shared library (DLL under Windows) when `ON`,
  build static library othervise. This option is `OFF` by default.
- `BUILD_EXAMPLES` - Builds the example programs
- `ENABLE_PACKAGE_CONFIG` - Generate and install [package config file](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#config-file-packages).
- `INSTALL_PKGCONFIG_MODULE` - Generate and install [pkg-config module](https://people.freedesktop.org/~dbn/pkg-config-guide.html).
- `BUILD_WITH_LOGGING` - Build with logging support (requires SpdLog)
- `CMAKE_INSTALL_PREFIX` - build install location, the same as `--prefix` option
  of `configure` script
  
  **Note**: For MSVC compiler `ENABLE_STATIC_RUNTIME`is deprecated for CMake >= 3.15, see
  policy [CMP0091](https://cmake.org/cmake/help/latest/policy/CMP0091.html).
  Use `CMAKE_MSVC_RUNTIME_LIBRARY` option instead.
- `ENABLE_STATIC_RUNTIME` - enable static runtime on Windows platform (MSVC and
  MinGW), `OFF` by default.

## Examples
Check out the examples folder for how to integrate into your app.
