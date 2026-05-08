cmake_minimum_required(VERSION 3.16)
project(GameChatPro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    WebEngine
    WebSockets
    Multimedia
)

# Find Opus library
find_package(PkgConfig)
pkg_check_modules(OPUS REQUIRED opus)

# Enable automatic moc, uic, rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Collect source files
file(GLOB_RECURSE SOURCES
    "flareirc/*.cpp"
    "flareirc/*.h"
    "flareirc/*.ui"
    "flareirc/*.qrc"
)

# Create executable
add_executable(GameChatPro ${SOURCES})

# Link libraries
target_link_libraries(GameChatPro PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::WebEngine
    Qt6::WebSockets
    Qt6::Multimedia
    ${OPUS_LIBRARIES}
)

# Include directories
target_include_directories(GameChatPro PRIVATE
    ${OPUS_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/flareirc
)

# Set target properties
set_target_properties(GameChatPro PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
