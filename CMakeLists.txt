cmake_minimum_required(VERSION 3.20)
project(oop_lab_4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(figures
    src/Figure.cpp
    src/Sphere.cpp
    src/Cube.cpp
    src/Cone.cpp
    src/FigureCollection.cpp
)

target_include_directories(figures PUBLIC src/include)

if(MSVC)
    target_compile_options(figures PRIVATE /W4)
else()
    target_compile_options(figures PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    add_executable(oop_lab_4 main.cpp)
    target_link_libraries(oop_lab_4 PRIVATE figures)

    if(MSVC)
        target_compile_options(oop_lab_4 PRIVATE /W4)
    else()
        target_compile_options(oop_lab_4 PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()

include(CTest)

if(BUILD_TESTING AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests.cpp")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(run_tests tests.cpp)
    target_link_libraries(run_tests PRIVATE figures GTest::gtest_main)

    if(MSVC)
        target_compile_options(run_tests PRIVATE /W4)
    else()
        target_compile_options(run_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    include(GoogleTest)
    gtest_discover_tests(run_tests)
endif()
