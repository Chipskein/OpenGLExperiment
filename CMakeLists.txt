cmake_minimum_required(VERSION 3.0)
project(Experiment)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Experiment/libs/glfw)

#option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
#option(ASSIMP_BUILD_SAMPLES OFF)
#option(ASSIMP_BUILD_TESTS OFF)
#add_subdirectory(Experiment/libs/assimp)

#option(BUILD_BULLET2_DEMOS OFF)
#option(BUILD_CPU_DEMOS OFF)
#option(BUILD_EXTRAS OFF)
#option(BUILD_OPENGL3_DEMOS OFF)
#option(BUILD_UNIT_TESTS OFF)
#add_subdirectory(Experiment/libs/bullet)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(Experiment/headers/
                    #Experiment/libs/assimp/include/
                    #Experiment/libs/bullet/src/
                    Experiment/libs/glad/include/
                    Experiment/libs/glfw/include/
                    Experiment/libs/glm/
                    Experiment/libs/stb/)

file(GLOB VENDORS_SOURCES Experiment/libs/glad/src/glad.c)
file(GLOB PROJECT_HEADERS Experiment/headers/*.hpp)
file(GLOB PROJECT_SOURCES Experiment/src/*.cpp)
file(GLOB PROJECT_SHADERS Experiment/resources/shaders/*.comp
                          Experiment/resources/shaders/*.frag
                          Experiment/resources/shaders/*.geom
                          Experiment/resources/shaders/*.vert)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES})
target_link_libraries(${PROJECT_NAME} glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Experiment/resources/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_SHADERS})