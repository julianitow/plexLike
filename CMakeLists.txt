cmake_minimum_required(VERSION 3.14)
include(FetchContent)

set(CXX_STANDARD_REQUIRED 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PlexLike VERSION 0.0 LANGUAGES C CXX)

find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(${PROJECT_NAME} 
    main.cpp 
    Server.cpp 
    FilesServices.cpp 
    bdd/Database.cpp 
    bdd/DatabaseService.cpp
    Entities/User.cpp
    Media/Media.cpp
    Media/Movie.cpp
    Media/Library/Library.cpp
    Media/MediaManager/MediaManager.cpp
)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES 
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_link_directories(${PROJECT_NAME}
    PUBLIC
        /usr/local/lib64/mariadb/
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        PkgConfig::Pistache
        nlohmann_json::nlohmann_json
        pthread
        mariadbcpp
        magic
)