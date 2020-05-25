# OboeLibraryDemo
This repository contains Android Studio's CPP Native Project with Oboe library included. Oboe is a C++ library which makes it easy to build high-performance audio apps on Android. It was created primarily to allow developers to target a simplified API that works across multiple API levels back to API level 16 (Jelly Bean).

(Desc from: [Oboe](https://github.com/google/oboe))

# Dev. Environment Setup
## Android Studio:
1. Install Android Studio Ver 3.6 (latest release before 4.0) from https://developer.android.com/studio
2. Open SDK Manager 
3. Install SDK Platforms:
    - Android 10.0 (Q) - API Lv.29 (Latest)
    - Android 7.0 (Nougat) - API Lv.24
4. Install SDK Tools:
    - Android SDK Build-Tools 30-rc4
    - GPU Debugging Tools
    - LLDB
    - Android NDK Build Tools ver:
      - 21.1.6352462 (latest)
      - 20.0.5594570
    - Cmake

## Create Native C++ Project with [Oboe Library](https://github.com/google/oboe):

1. Start create new project
2. On the "Phone and Tablet" tab, select **"Native C++"**, click next
3. Configure your application name and save location
4. Languange: Java, **Minimum SDK** set to **API 23**, click NEXT
5. Select C++ Standard to **C++14**, Click Finish
6. Open the project directory folder, head to cpp folder, the path should be like this: 
    ```
    "..\YourProject\app\src\main\cpp"
    ```
7. Open cmd there, add Oboe Library as a [submodule](https://gist.github.com/gitaarik/8735255):
    ```
    git submodule add https://github.com/google/oboe
    ```
8. Update CMakeLists.txt, here's the complete example:
    ```
    # For more information about using CMake with Android Studio, read the
    # documentation: https://d.android.com/studio/projects/add-native-code.html

    # Sets the minimum version of CMake required to build the native library.

    cmake_minimum_required(VERSION 3.4.1)

    # Creates and names a library, sets it as either STATIC
    # or SHARED, and provides the relative paths to its source code.
    # You can define multiple libraries, and CMake builds them for you.
    # Gradle automatically packages shared libraries with your APK.

    add_library(
            # Sets the name of the library.
            native-lib
            # Sets the library as a shared library.
            SHARED

            # Provides a relative path to your source file(s).
            native-lib.cpp
            )
    # Searches for a specified prebuilt library and stores the path as a
    # variable. Because CMake includes system libraries in the search path by
    # default, you only need to specify the name of the public NDK library
    # you want to add. CMake verifies that the library exists before
    # completing its build.
    find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )
    
    target_link_libraries( # Specifies the target library.
                        native-lib
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}

                        oboe)

    # Set the path to the Oboe directory.
    set (OBOE_DIR ./oboe)

    # Add the Oboe library as a subdirectory in your project.
    # add_subdirectory tells CMake to look in this directory to
    # compile oboe source files using oboe's CMake file.
    # ./oboe specifies where the compiled binaries will be stored
    add_subdirectory (${OBOE_DIR} ./oboe)

    # Specify the path to the Oboe header files.
    # This allows targets compiled with this CMake (application code)
    # to see public Oboe headers, in order to access its API.
    include_directories (${OBOE_DIR}/include)
    ```
  9. On the menu bar: `Build > Refresh Linked C++ Projects` 