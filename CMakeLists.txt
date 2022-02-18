# CMakeList.txt: GeneralizedMap 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("GeneralizedMap")

add_definitions(
  -DDATA_PATH=\"${PROJECT_SOURCE_DIR}/data\"
)

# 将源代码添加到此项目的可执行文件。
add_executable (GeneralizedMap "src/main.cpp" "src/Point.h")

# TODO: 如有需要，请添加测试并安装目标。
# TODO: 如有需要，请添加测试并安装目标。
set_target_properties(GeneralizedMap PROPERTIES 
  CXX_STANDARD 17
)

# Make the executable a default target to build & run in Visual Studio
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GeneralizedMap)