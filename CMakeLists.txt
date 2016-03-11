cmake_minimum_required(VERSION 3.2.2)
project(vlc_plugin_subtitles)

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(LIBVLC REQUIRED)
find_package(PythonLibs REQUIRED)

include_directories(include ${PYTON_INCLUDE_DIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -g -O2 -Wall -Wextra -fPIC -D__PLUGIN__ -D_FILE_OFFSET_BITS=64 -D_REENTRANT -D_THREAD_SAFE -DMODULE_STRING=\"subtitles\"")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPIC")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-no-undefined,-z,defs")

add_library(subtitles_plugin SHARED src/subtitles.c)
target_link_libraries(subtitles_plugin ${LIBVLCCORE_LIBRARY} ${PYTHON_LIBRARIES})

add_custom_command(TARGET subtitles_plugin POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:subtitles_plugin>" "~/.local/share/vlc/plugins")