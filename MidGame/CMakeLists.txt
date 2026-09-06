cmake_minimum_required(VERSION 3.20)

project(MidGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:\\Users\\User\\source\\SFML\\lib\\cmake\\SFML")
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(MidGame "MidGame.cpp" "MidGame.h"
    "src/Game/Player.cpp"
    "src/Game/Player.h"
    "src/Game/Game.cpp"
    "src/Game/Game.h"
    "src/Utilities/Utils.h"
    "src/Utilities/InputControls.h"
    "src/Utilities/InputControls.cpp"
)
target_include_directories(MidGame PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(MidGame PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)