cmake_minimum_required(VERSION 3.13)

set(PROJECT_ID projekt)

include_directories(
        include
)


set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        src/tests.cpp
)

set(SOURCES_FILES_TESTS
        test/tests.cpp
        test/main_test.cpp
        )



include(SetCommonConfig.cmake)
