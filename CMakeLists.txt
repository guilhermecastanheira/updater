cmake_minimum_required(VERSION 3.16)

project(updater LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

include(FetchContent)

# CPR to the HTTP requests
FetchContent_Declare(
  cpr
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
  GIT_TAG        1.14.2
)
set(CPR_CURL_USE_LIBPSL OFF CACHE BOOL "" FORCE)
set(CPR_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(cpr)

# ZIP to extract the zip file
FetchContent_Declare(
  zip
  GIT_REPOSITORY https://github.com/kuba--/zip.git
  GIT_TAG        v0.3.8
)
set(CMAKE_DISABLE_TESTING ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(zip)

# NLOHMANN_JSON to jason configuration file
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(updater main.cpp
  updatemanager.h updatemanager.cpp
  config.h config.cpp
  config.json.exemple)

target_link_libraries(updater PRIVATE cpr::cpr zip nlohmann_json)

include(GNUInstallDirs)
install(TARGETS updater
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
