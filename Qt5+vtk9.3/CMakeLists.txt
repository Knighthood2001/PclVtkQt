cmake_minimum_required(VERSION 3.10)

project(QtVTKTest)

# 设置Qt路径
set(CMAKE_PREFIX_PATH "I:/cpppackage/Qt/5.15.2/msvc2019_64")

# 查找Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# 设置VTK路径
set(VTK_DIR "C:/Program Files/PCL 1.14.0/3rdParty/VTK/lib/cmake/vtk-9.3")

# 查找VTK模块
find_package(VTK REQUIRED COMPONENTS
    CommonCore
    CommonDataModel
    FiltersSources
    InteractionStyle
    RenderingOpenGL2
    RenderingCore
    RenderingUI
    RenderingContextOpenGL2
    GUISupportQt
    RenderingQt
)

# 添加可执行文件
add_executable(QtVTKTest Qt_VTK_Test.cpp)

# 链接库
target_link_libraries(QtVTKTest
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    ${VTK_LIBRARIES}
)

# 设置包含目录
target_include_directories(QtVTKTest PRIVATE
    ${Qt5_INCLUDE_DIRS}
    ${VTK_INCLUDE_DIRS}
)

# 复制必要的DLL文件（Windows）
if(WIN32)
    add_custom_command(TARGET QtVTKTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "I:/cpppackage/Qt/5.15.2/msvc2019_64/bin/Qt5Core.dll"
            $<TARGET_FILE_DIR:QtVTKTest>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "I:/cpppackage/Qt/5.15.2/msvc2019_64/bin/Qt5Gui.dll"
            $<TARGET_FILE_DIR:QtVTKTest>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "I:/cpppackage/Qt/5.15.2/msvc2019_64/bin/Qt5Widgets.dll"
            $<TARGET_FILE_DIR:QtVTKTest>
        COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:QtVTKTest>/platforms
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "I:/cpppackage/Qt/5.15.2/msvc2019_64/plugins/platforms/qwindows.dll"
            $<TARGET_FILE_DIR:QtVTKTest>/platforms/
    )
endif()