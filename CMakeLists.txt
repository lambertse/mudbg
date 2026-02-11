cmake_minimum_required(VERSION 3.5)
project(mudbg)

# Force Debug build type
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(REDIS_BUILD ON)
set(REDIS_ENABLE_TEST ON)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

set(MUDBG_ENABLE_TEST OFF)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define compile flags for Debug and Release modes
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

# Include all header files in the include directory
file(GLOB MUDBG_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/mudbg/*.h")
file(GLOB MUDBG_SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(mudbg ${MUDBG_SOURCE_FILES})
target_include_directories(mudbg PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mudbg
)

# GTest Configuration
if(MUDBG_ENABLE_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

