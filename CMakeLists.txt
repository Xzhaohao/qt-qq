cmake_minimum_required(VERSION 3.19)
project(QtQQ)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.12.12/5.12.12/msvc2017_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Sql Xml Network WebChannel WebEngineWidgets WebEngine)
set(REQUIRED_LIBS_QUALIFIED
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::Xml
        Qt5::Network
        Qt5::WebChannel
        Qt5::WebEngine
        Qt5::WebEngineWidgets)

add_executable(
        ${PROJECT_NAME} main.cpp
        views/main/mainWindow.cpp
        views/main/mainWindow.h
        components/titleBar/titleBar.cpp
        components/titleBar/titleBar.h
        components/titleBar/buttonType.h
        views/base/baseWindow.cpp
        views/base/baseWindow.h
        utils/commonUtils.cpp
        utils/commonUtils.h
        manger/notifyManger.cpp
        manger/notifyManger.h
        utils/customProxyStyle.h
        views/login/login.cpp
        views/login/login.h
        views/main/mainProxyStyle.h
        views/skin/skin.cpp
        views/skin/skin.h
        components/clickLabel/clickLabel.cpp
        components/clickLabel/clickLabel.h
        components/systemTray/systemTray.cpp
        components/systemTray/systemTray.h
        components/systemTray/customMenu.cpp
        components/systemTray/customMenu.h
        views/main/rootContactItem.cpp
        views/main/rootContactItem.h
        components/contactItem/contactItem.cpp
        components/contactItem/contactItem.h
        views/talk/talkWindow.cpp
        views/talk/talkWindow.h
        views/talk/talkWindowShell.cpp
        views/talk/talkWindowShell.h
        views/emotion/emotionWindow.cpp
        views/emotion/emotionWindow.h
        views/emotion/emotionLabelItem.cpp
        views/emotion/emotionLabelItem.h
        views/talk/talkWindowItem.cpp
        views/talk/talkWindowItem.h
        manger/windowManger.cpp
        manger/windowManger.h
        components/msgEdit/QMsgTextEdit.cpp
        components/msgEdit/QMsgTextEdit.h
        components/msgView/msgWebView.cpp
        components/msgView/msgWebView.h
        views/sendFile/sendFile.cpp
        views/sendFile/sendFile.h
        views/receiveFile/receiveFile.cpp
        views/receiveFile/receiveFile.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

# 找到对应的qt模块，名字为qmake中QT += <name>中的name首字母大写后加上Qt5前缀
# 例如core为QtCore，你也可以去${CMAKE_PREFIX_PATH}的目录中找到正确的模块名
# 如果不想使用系统qt，这样写（注意NO_DEFAULT_PATH参数，它会让find_package跳过系统目录的查找）：
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)

    #    WebEngineWidgets
    if (TRUE)
        MESSAGE("copy WebEngineWidgets")
        # copy WebEngineWidgets 模块的依赖 *.dll
        foreach (WebEngineWidgets_dependency Network Positioning PrintSupport Qml QmlModels Quick QuickWidgets WebChannel WebEngineCore WebEngineWidgets)
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/bin/Qt5${WebEngineWidgets_dependency}${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
        endforeach (WebEngineWidgets_dependency)
        # copy  WebEngineWidgets 模块的依赖 QtWebEngineProcess.exe
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy "${QT_INSTALL_PATH}/bin/QtWebEngineProcess${DEBUG_SUFFIX}.exe"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
        # copy  WebEngineWidgets 模块的依赖 translations 目录
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${QT_INSTALL_PATH}/translations"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/translations")
        # copy  WebEngineWidgets 模块的依赖 translations 目录
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${QT_INSTALL_PATH}/resources"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources")
    endif ()
endif ()
