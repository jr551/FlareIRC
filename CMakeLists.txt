cmake_minimum_required(VERSION 3.21)

project(GameChatPro LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    Network
    WebEngineCore
    WebEngineWidgets
    WebSockets
    Multimedia
)

# Find Opus codec library
find_package(PkgConfig REQUIRED)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(OPUS opus)
endif()

if(OPUS_FOUND)
    add_library(Opus::Opus ALIAS IMPORTED)
    set_target_properties(Opus::Opus PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${OPUS_INCLUDE_DIRS}"
        INTERFACE_LINK_LIBRARIES "${OPUS_LIBRARIES}"
    )
else()
    find_library(OPUS_LIBRARY NAMES opus opus-0)
    find_path(OPUS_INCLUDE_DIR NAMES opus/opus.h)
    if(OPUS_LIBRARY AND OPUS_INCLUDE_DIR)
        add_library(Opus::Opus UNKNOWN IMPORTED)
        set_target_properties(Opus::Opus PROPERTIES
            IMPORTED_LOCATION "${OPUS_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${OPUS_INCLUDE_DIR}"
        )
    else()
        message(FATAL_ERROR "Opus library not found. Install opus-dev or opus package.")
    endif()
endif()

# Source files
set(SOURCES
    flareirc/main.cpp
    flareirc/connectwindow.cpp
    flareirc/ircsocket.cpp
    flareirc/talkwindow.cpp
    flareirc/chattab.cpp
    flareirc/privatemessagetab.cpp
    flareirc/servertab.cpp
    flareirc/talkwindowtab.cpp
    flareirc/inputdialog.cpp
    flareirc/optionswindow.cpp
    flareirc/scriptmanager.cpp
    flareirc/privatechatwindow.cpp
    flareirc/chatwindow.cpp
)

# Header files
set(HEADERS
    flareirc/connectwindow.h
    flareirc/ircsocket.h
    flareirc/talkwindow.h
    flareirc/chattab.h
    flareirc/privatemessagetab.h
    flareirc/servertab.h
    flareirc/talkwindowtab.h
    flareirc/inputdialog.h
    flareirc/optionswindow.h
    flareirc/scriptmanager.h
    flareirc/privatechatwindow.h
    flareirc/chatwindow.h
)

# UI forms
set(FORMS
    flareirc/connectwindow.ui
    flareirc/talkwindow.ui
    flareirc/chattab.ui
    flareirc/privatemessagetab.ui
    flareirc/servertab.ui
    flareirc/inputdialog.ui
    flareirc/optionswindow.ui
    flareirc/privatechatwindow.ui
)

# Resource files
set(RESOURCES
    flareirc/flareirc.qrc
)

# Platform-specific settings
if(WIN32)
    set(APP_ICON_RESOURCES
        flareirc/FlareIRC.rc
    )
endif()

# Create executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${RESOURCES}
    ${APP_ICON_RESOURCES}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/flareirc
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    Qt6::WebEngineCore
    Qt6::WebEngineWidgets
    Qt6::WebSockets
    Qt6::Multimedia
    Opus::Opus
)

# Compile definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    QT_DEPRECATED_WARNINGS
)

# Windows-specific settings
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        optimus  # NVIDIA Optimus support
        dwmapi   # Windows DWM API
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
        RC_ICONS "flareirc/icon.ico"
    )
endif()

# macOS-specific settings
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_ICON_FILE icon.icns
        BUNDLE_IDENTIFIER "com.gamechatpro.app"
    )
    target_sources(${PROJECT_NAME} PRIVATE
        flareirc/icon.icns
    )
    set_source_files_properties(flareirc/icon.icns PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )
endif()

# Linux-specific settings
if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${X11_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES})
endif()

# Installation
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)
