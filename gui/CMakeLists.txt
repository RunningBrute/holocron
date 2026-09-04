find_package(Qt6 REQUIRED COMPONENTS Quick)

set(CMAKE_AUTOMOC ON)

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