cmake_minimum_required(VERSION 3.16)

project(HolocronGui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_add_executable(holocron-gui
    main.cpp
    NodeManager.cpp
    NodeManager.h)

qt_add_qml_module(holocron-gui
    URI HolocronGui
    VERSION 1.0
    QML_FILES
        Main.qml
)

target_link_libraries(holocron-gui PRIVATE Qt6::Quick)