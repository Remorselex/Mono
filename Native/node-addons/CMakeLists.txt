cmake_minimum_required(VERSION 3.15)
project(native)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

execute_process(
        COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_INCLUDE
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

include_directories(${NODE_ADDON_API_DIR})
include_directories(${CMAKE_JS_INC})
include_directories(${CMAKE_SOURCE_DIR}/../../Cpp/include)  # Ваш C++ код!

#исходники
file(GLOB SOURCE_FILES "src/native/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES
        PREFIX ""
        SUFFIX ".node"
        CXX_STANDARD 17
)

target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})


target_compile_definitions(${PROJECT_NAME} PRIVATE NAPI_VERSION=8)

if (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_RPATH ON
            BUILD_WITH_INSTALL_RPATH ON
    )
endif ()
