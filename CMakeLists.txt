cmake_minimum_required(VERSION 3.16)

project(QtAndroidViewShare VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)

set(DEVELOPER_DEFAULTS ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core  Quick CorePrivate )
find_package(Qt6 REQUIRED  COMPONENTS Quick PrintSupport)

if (Qt6_FOUND)
  set(Qt Qt)
else()
  set(Qt Qt5)
endif()

qt_add_executable(QtAndroidViewShare
    main.cpp
    resourceExample.qrc
)

# Extra QML File properties
set_source_files_properties(
    Core/ShareUtils.qml
    ResourceCreator.qml
    PROPERTIES
        QT_QML_SINGLETON_TYPE True
)

qt_add_qml_module(QtAndroidViewShare
    URI "QtAndroidViewShare"
    VERSION 1.0

    QML_FILES
        Main.qml
        Core/ShareUtils.qml
        ResourceCreator.qml

    SOURCES
        ResourceCreatorCpp.h
        ResourceCreatorCpp.cpp

        Core/shareutils/ShareUtilsCpp.h
        Core/shareutils/ShareUtilsCpp.cpp
        Core/shareutils/PlatformShareUtils.h
        Core/shareutils/PlatformShareUtils.cpp

        android/AndroidManifest.xml
        android/src/org/shareluma/utils/QShareUtils.java
        android/src/org/shareluma/utils/QSharePathResolver.java
        android/src/org/shareluma/activity/QShareActivity.java
)

include_directories(Core/shareutils)

target_link_libraries(QtAndroidViewShare
    PRIVATE
        ${Qt}::Quick
        ${Qt}::Core
        ${Qt}::CorePrivate
        ${Qt}::PrintSupport
)

set_target_properties(QtAndroidViewShare PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
)

install(TARGETS QtAndroidViewShare
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
