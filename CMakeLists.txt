cmake_minimum_required(VERSION 3.5)

file(STRINGS "${CMAKE_SOURCE_DIR}/makespec/VERSION" VERSION)
file(STRINGS "${CMAKE_SOURCE_DIR}/makespec/BUILDVERSION" BUILD_VERSION)
file(STRINGS "${CMAKE_SOURCE_DIR}/makespec/VERSIONSUFFIX" VERSION_SUFFIX)

set(VERSION_STRING "${VERSION}${VERSION_SUFFIX}")
set(VERSION_LIST ${VERSION})
string(REPLACE "." ";" VERSION_LIST ${VERSION_LIST})
separate_arguments(VERSION_LIST)

project(notepanda LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DVERSION_STRING="${VERSION_STRING}")
add_definitions(-DXTOSTRUCT_QT)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


# =======================
# Notepanda Build Message
# =======================

message(" ")
message("Notepanda Version: ${VERSION_STRING}")
message("Notepanda Build Version: ${BUILD_VERSION}")
message("Notepanda Build Type: ${CMAKE_BUILD_TYPE}")
message("|-------------------------------------------------|")
message("| Notepanda, A Cross Platform Notepad.            |")
message("| Based on C++ & Qt.                              |")
message("| Licenced under MIT                              |")
message("|                                                 |")
message("| You may only use this program to the extent     |")
message("| permitted by local law.                         |")
message("|                                                 |")
message("| See: https://opensource.org/licenses/MIT        |")
message("|-------------------------------------------------|")
message("| GitHub: https://github.com/ChungZH/notepanda    |")
message("| Welcome to contribute!                          |")
message("|-------------------------------------------------|")
message(" ")

find_package(Qt5 COMPONENTS Widgets Core Quick QuickControls2 REQUIRED)
find_package(KF5SyntaxHighlighting REQUIRED)

if(WIN32)
    set(GUI_TYPE WIN32)
elseif(APPLE)
    set(GUI_TYPE MACOSX_BUNDLE)
endif()

# =============================
# Notepanda Sources and Headers
# =============================
set(SOURCES
    src/main.cpp
    qml.qrc
    resources.qrc
    src/CodeEditor/Backend/codeeditorbackend.cpp
    src/CodeEditor/Backend/codeeditorbackend.h
    src/common/nphelpers.cpp
    src/common/nphelpers.h
    src/aboutwindowbackend.hpp
    src/CodeEditor/Backend/linenumbers.hpp
    src/settings/configmanager.h
    src/settings/configmanager.cpp
    src/preferenceswindowbackend.hpp
)

if(ANDROID)
    add_library(notepanda SHARED
      ${SOURCES}
      ${GUI_TYPES}
    )
else()
    add_executable(notepanda
      ${SOURCES}
      ${GUI_TYPES}
    )
endif()

if(UNIX AND NOT APPLE AND NOT WIN32)
    install(TARGETS notepanda RUNTIME DESTINATION bin)
    install(FILES assets/notepanda.desktop DESTINATION share/applications)
    install(FILES assets/notepanda.png DESTINATION share/icons/hicolor/256x256/apps)
endif()

# Directories to look for dependencies
set(DIRS "${CMAKE_BINARY_DIR}")

# Path used for searching by FIND_XXX(), with appropriate suffixes added
if(CMAKE_PREFIX_PATH)
    foreach(dir ${CMAKE_PREFIX_PATH})
        list(APPEND DIRS "${dir}/bin" "${dir}/lib")
    endforeach()
endif()

# =========
# Packaging
# =========

set(CPACK_PACKAGE_NAME "Notepanda")
set(CPACK_PACKAGE_VENDOR "ChungZH")
set(CPACK_PACKAGE_VERSION ${VERSION_STRING})
set(CPACK_PACKAGE_DESCRIPTION "A simple cross-platform notepad.")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/ChungZH/notepanda")
set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/assets/panda.ico")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.md")

if(MSVC)
   set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION .)
endif()

include(InstallRequiredSystemLibraries)

if(WIN32)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
    if (BUILD_NSIS)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND windeployqt ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.exe --compiler-runtime --no-translations --verbose 2 --dir ${CMAKE_BINARY_DIR}/winqt/
            )
        install(DIRECTORY ${CMAKE_BINARY_DIR}/winqt/ DESTINATION .)
    endif()
    set(APPS "\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.exe")
endif()

if(WIN32)
    if(BUILD_NSIS)
        set(CPACK_GENERATOR "NSIS")
        set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/images\\\\panda.ico")
        set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/images/panda.ico")
        set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/images/panda.ico")
        set(CPACK_NSIS_DISPLAY_NAME "Notepanda")
        set(CPACK_NSIS_PACKAGE_NAME "Notepanda")
        set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
            CreateShortCut \\\"$DESKTOP\\\\Notepanda.lnk\\\" \\\"$INSTDIR\\\\notepanda.exe\\\"
            CreateDirectory \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Notepanda\\\"
            CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Notepanda\\\\Notepanda.lnk\\\" \\\"$INSTDIR\\\\notepanda.exe\\\"
            WriteRegStr HKLM \\\"Software\\\\Microsoft\\\\Windows\\\\CurrentVersion\\\\Uninstall\\\\notepanda\\\" \\\"DisplayIcon\\\" \\\"$INSTDIR\\\\notepanda.exe\\\"
            WriteRegStr HKLM \\\"Software\\\\Microsoft\\\\Windows\\\\CurrentVersion\\\\Uninstall\\\\notepanda\\\" \\\"HelpLink\\\" \\\"https://github.com/ChungZH/notepanda\\\"
            WriteRegStr HKLM \\\"Software\\\\Microsoft\\\\Windows\\\\CurrentVersion\\\\Uninstall\\\\notepanda\\\" \\\"InstallLocation\\\" \\\"$INSTDIR\\\"
            WriteRegStr HKLM \\\"Software\\\\Microsoft\\\\Windows\\\\CurrentVersion\\\\Uninstall\\\\notepanda\\\" \\\"URLUpdateInfo\\\" \\\"https://github.com/ChungZH/notepanda/releases\\\"
            WriteRegStr HKLM \\\"Software\\\\Microsoft\\\\Windows\\\\CurrentVersion\\\\Uninstall\\\\notepanda\\\" \\\"URLInfoAbout\\\" \\\"https://github.com/ChungZH/notepanda\\\"
        ")
        set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
            Delete \\\"$DESKTOP\\\\Notepanda.lnk\\\"
            Delete \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Notepanda\\\\Notepanda.lnk\\\"
            RMDir \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Notepanda\\\"
            DeleteRegKey HKLM \\\"Software\\\\Microsoft\\\\Windows\\\\CurrentVersion\\\\Uninstall\\\\notepanda\\\"
        ")
        set(CPACK_PACKAGE_INSTALL_DIRECTORY "notepanda")
    endif()
endif()

if(UNIX)
    if(BUILD_DEB)
        set(CPACK_GENERATOR "DEB")
        set(CPACK_DEBIAN_PACKAGE_NAME "Notepanda")
        set(CPACK_PACKAGE_CONTACT "chungzh07@gmail.com")
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "ChungZH")
        set(CPACK_DEBIAN_PACKAGE_DEPENDS "qtbase5-dev, qttools5-dev, libkf5syntaxhighlighting-dev")
    endif()

    #if(BUILD_RPM)
    #    set(CPACK_GENERATOR "RPM")
    #    set(CPACK_RPM_PACKAGE_LICENSE "MIT")
    #endif()
endif()

if(WIN32)
    list(APPEND DIRS "${KF5SyntaxHighlighting_DIR}/../../../bin/")
    install(CODE "include(BundleUtilities)
          fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")")
endif()

include(CPack)

target_compile_definitions(notepanda
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(notepanda Qt5::Core Qt5::Widgets Qt5::Quick Qt5::QuickControls2 KF5::SyntaxHighlighting)
