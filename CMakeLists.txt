cmake_minimum_required(VERSION 3.14)

set(CXX_STANDARD_REQUIRED 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PlexLike VERSION 0.0 LANGUAGES C CXX)

find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)

add_executable(${PROJECT_NAME} main.cpp Server.cpp)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES 
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        PkgConfig::Pistache
)