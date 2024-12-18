cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_ID projekt)

include_directories(
        include
)

set(SOURCE_FILES
        src/factory.cpp
        src/helpers.cpp
        src/nodes.cpp
        src/package.cpp
        src/reports.cpp
        src/simulation.cpp
        src/storage_types.cpp

)

set(SOURCES_FILES_TESTS
        test/tests.cpp
        test/main_gtest.cpp
        )

include(SetCommonConfig.cmake)
