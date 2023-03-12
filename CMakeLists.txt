cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lotus)

#file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} src/main.cpp src/RenderHandler.cpp src/RenderHandler.h src/BrowserClient.cpp src/BrowserClient.h src/WebCore.cpp src/WebCore.h src/WebApp.cpp src/WebApp.h)
#add_library(glew32 SHARED "C:/Program Files (x86)/Steam/steamapps/common/Geometry Dash/glew32.dll")
#set_target_properties(glew32 PROPERTIES LINKER_LANGUAGE CXX)

set(CMAKE_SIZEOF_VOID_P 4)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    # ensure 32 bit on clang
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -target i386-pc-windows-msvc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -target i386-pc-windows-msvc")
    add_definitions("--target=i386-pc-windows-msvc")
endif()

set(CEF_CMAKE_OUTPUT_DIR vendor/cef2)
set(CEF_USE_SANDBOX OFF)
#set(CEF_VERSION 106.0.26+ge105400+chromium-106.0.5249.91)
include(${CMAKE_SOURCE_DIR}/vendor/cef-cmake/cmake/cef_cmake.cmake)

set(ONLY_LIBS ON)
#set(BUILD_SHARED_LIBS ON)

add_subdirectory(vendor/minhook)
add_subdirectory(vendor/cocos-headers)
add_subdirectory(vendor/cef-cmake)
add_subdirectory(vendor/glew-cmake)

target_link_libraries(${PROJECT_NAME} cocos2d minhook opengl32 libglew_static cefdll_wrapper)

add_executable(lotus_sub subproccess/subproccess.cpp)
target_link_libraries(lotus_sub cefdll_wrapper)