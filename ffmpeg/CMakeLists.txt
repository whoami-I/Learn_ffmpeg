# For more information about using CMake with Android Studio, read the
 # documentation: https://d.android.com/studio/projects/add-native-code.html

 # Sets the minimum version of CMake required to build the native library.

 cmake_minimum_required(VERSION 3.4.1)
 ##### no need to set output path
 #set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})

 # Specifies a library name, specifies whether the library is STATIC or
 # SHARED, and provides relative paths to the source code. You can
 # define multiple libraries by adding multiple add.library() commands,
 # and CMake builds them for you. When you build your app, Gradle
 # automatically packages shared libraries with your APK.
###############设置头文件的搜索路径######################
include_directories(
        ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg/ffmpeg
)
 add_library( # Sets the name of the library.
         zplay-lib

         # Sets the library as a shared library.
         SHARED

         # Provides a relative path to your source file(s).
         ${CMAKE_SOURCE_DIR}/src/main/cpp/zplay-lib.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)


 # Specifies libraries CMake should link to your target library. You
 # can link multiple libraries, such as libraries you define in this
 # build script, prebuilt third-party libraries, or system libraries.

 target_link_libraries( # Specifies the target library.
         zplay-lib

         # Links the target library to the log library
         # included in the NDK.
         ${log-lib}
         libavcodec-58
         libavfilter-7
         libavformat-58
         libavutil-56
         libswresample-3
         libavdevice-58
         libswscale-5)


 # 编解码
 add_library(libavcodec-58
         SHARED
         IMPORTED)
 set_target_properties(libavcodec-58 PROPERTIES IMPORTED_LOCATION
         ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libavcodec-58.so)
 # 和多媒体设备交互的类库
 add_library(libavdevice-58
         SHARED
         IMPORTED)
 set_target_properties(libavdevice-58 PROPERTIES IMPORTED_LOCATION
         ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libavdevice-58.so)
 # 图像的pixel format处理
 add_library(libavfilter-7
         SHARED
         IMPORTED)
 set_target_properties(libavfilter-7 PROPERTIES IMPORTED_LOCATION
         ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libavfilter-7.so)
 # 格式
 add_library(libavformat-58
         SHARED
         IMPORTED)
 set_target_properties(libavformat-58 PROPERTIES IMPORTED_LOCATION
         ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libavformat-58.so)

 # 工具函数
 add_library(libavutil-56
         SHARED
         IMPORTED)
 set_target_properties(libavutil-56 PROPERTIES IMPORTED_LOCATION
         ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libavutil-56.so)

 # 音频重采样，采样格式转换和混合库
 add_library(libswresample-3
         SHARED
         IMPORTED)
 set_target_properties(libswresample-3 PROPERTIES IMPORTED_LOCATION
         ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libswresample-3.so)

 # 缩放处理
 add_library(libswscale-5
         SHARED
         IMPORTED)
 set_target_properties(libswscale-5 PROPERTIES IMPORTED_LOCATION
         ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libswscale-5.so)