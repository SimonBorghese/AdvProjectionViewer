cmake_minimum_required(VERSION 3.28)
project(AdvProjectionViewer)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

add_executable(AdvProjectionViewer WIN32 main.cpp
        src/Window.c
        src/Window.h
        src/Render.c
        src/Render.h
        imgui/imgui_demo.cpp
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_impl_opengl3.cpp
        imgui/imgui_impl_sdl2.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_tables.cpp
        src/NDI.c
        src/NDI.h)

target_link_libraries(AdvProjectionViewer "${CMAKE_SOURCE_DIR}/NDI/Processing.NDI.Lib.x64.lib" "${CMAKE_SOURCE_DIR}/SDL2/SDL2.lib"  ${OPENGL_LIBRARIES})
include_directories("${CMAKE_SOURCE_DIR}/NDI/include" "${CMAKE_SOURCE_DIR}/SDL2/include" "${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/glad" "${CMAKE_SOURCE_DIR}/imgui")

