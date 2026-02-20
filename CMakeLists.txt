cmake_minimum_required(VERSION 3.22)
project(WIM
    VERSION 1.0.0
    LANGUAGES C
)

# C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Generate compile_commands.json for vscode intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose build type" FORCE)
endif()

# Sanitizer options
option(ENABLE_ASAN "Address Sanitizer" OFF)
option(ENABLE_TSAN "Thread Sanitizer" OFF)
option(ENABLE_MSAN "Memory Sanitizer" OFF)

# Check for mutually exclusive sanitizers
if(ENABLE_ASAN AND ENABLE_TSAN)
    message(FATAL_ERROR "Address Sanitizer and Thread Sanitizer cannot be enabled simultaneously")
endif()

if(ENABLE_ASAN AND ENABLE_MSAN)
    message(FATAL_ERROR "Address Sanitizer and Memory Sanitizer cannot be enabled simultaneously")
endif()

if(ENABLE_TSAN AND ENABLE_MSAN)
    message(FATAL_ERROR "Thread Sanitizer and Memory Sanitizer cannot be enabled simultaneously")
endif()

# Apply sanitizers
if(ENABLE_ASAN)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()

if(ENABLE_TSAN)
    add_compile_options(-fsanitize=thread)
    add_link_options(-fsanitize=thread)
endif()

if(ENABLE_MSAN)
    add_compile_options(-fsanitize=memory -fPIE -fno-omit-frame-pointer)
    add_link_options(-fsanitize=memory -pie)
endif()

# WIM
add_library(wimlib 
src/memory_hooks.c
# ds
src/ds/dynamic_array.c
src/ds/linked_list.c
# alloc
)
target_include_directories(wimlib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(wimlib PRIVATE -Wall -Wextra -pedantic)

# Examples
add_executable(dyn_arr_ex examples/dyn_arr_ex.c)
target_include_directories(dyn_arr_ex PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(dyn_arr_ex PRIVATE wimlib)
target_compile_options(dyn_arr_ex PRIVATE -Wall -Wextra -pedantic)

add_executable(s_linked_list_ex examples/s_linked_list_ex.c)
target_include_directories(s_linked_list_ex PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(s_linked_list_ex PRIVATE wimlib)
target_compile_options(s_linked_list_ex PRIVATE -Wall -Wextra -pedantic)

add_executable(d_linked_list_ex examples/d_linked_list_ex.c)
target_include_directories(d_linked_list_ex PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(d_linked_list_ex PRIVATE wimlib)
target_compile_options(d_linked_list_ex PRIVATE -Wall -Wextra -pedantic)

# Summary
message(STATUS "")
message(STATUS "=======================================================")
message(STATUS "Build:                              ${CMAKE_BUILD_TYPE}")

message(STATUS "C compiler:                         ${CMAKE_C_COMPILER}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
message(STATUS "C Debug flags:                      ${CMAKE_C_FLAGS_DEBUG}")
else()
message(STATUS "C Release flags:                    ${CMAKE_C_FLAGS_RELEASE}")
endif()

message(STATUS "Generator:                          ${CMAKE_GENERATOR}")

message(STATUS "Enable Address Sanitizer:           ${ENABLE_ASAN}")
message(STATUS "Enable Thread Sanitizer:            ${ENABLE_TSAN}")
message(STATUS "Enable Memory Sanitizer:            ${ENABLE_MSAN}")
message(STATUS "=======================================================")
message(STATUS "")