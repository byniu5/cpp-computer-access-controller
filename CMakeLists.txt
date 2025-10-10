cmake_minimum_required(VERSION 3.15)
project(ComputerAccessController)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# Source files
set(SOURCES
    src/main.cpp
    src/MainFrame.cpp
    src/ScheduleManager.cpp
    src/TimeChecker.cpp
    src/SystemController.cpp
)

set(HEADERS
    src/MainFrame.h
    src/ScheduleManager.h
    src/TimeChecker.h
    src/SystemController.h
)

# Create executable
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

# Windows specific settings
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE _UNICODE)
endif()
