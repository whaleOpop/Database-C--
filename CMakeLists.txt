cmake_minimum_required(VERSION 3.10)
project(DatabaseCpp VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_subdirectory(Models)
add_executable(DatabaseCpp main.cpp)

target_link_libraries(DatabaseCpp field table datebase bit datetime int parent varchar)

if (WIN32)
    add_compile_options("/source-charset:utf-8" "/execution-charset:utf-8")
elseif(UNIX)
    add_compile_options("-finput-charset=UTF-8" "-fexec-charset=UTF-8")
endif()

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



include(CPack)
