cmake_minimum_required(VERSION 4.0)
project(cpp_parental_controller)

set(CMAKE_CXX_STANDARD 20)
# To avoid "Missing MSVCP140.dll" errors on the target machine, I should statically link the runtime libraries.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Fix for MinGW: Statically link standard libraries to avoid "Entry Point Not Found" or missing DLL errors
if(MINGW OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

set(SOURCES
        main.cpp
        src/scripts/Scripts.cpp
        src/timer/Timer.cpp
        src/data/Data.cpp
        src/data/Data.h
        src/scripts/notifications.cpp
        src/scripts/Notifications.h
)
set(HEADERS
        src/timer/Timer.h
        src/scripts/Scripts.h
)

add_executable(${PROJECT_NAME}
                ${SOURCES}
)

##################### TESTS ######################

enable_testing()

# Fetch Google Test.
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
# Actually downloads and builds GTest.
FetchContent_MakeAvailable(googletest)
# Prevent CLion from auto-discovering individual tests.
set(CMAKE_GTEST_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)

add_executable(tests
        lib/tests/TimerTest.cpp
        src/timer/Timer.cpp
        lib/tests/DataTest.cpp
        src/data/Data.cpp
)

# Links GTest to test executable.
target_link_libraries(tests
        GTest::gtest_main
)