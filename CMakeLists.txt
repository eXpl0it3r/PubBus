cmake_minimum_required(VERSION 3.15)

project(PubBus LANGUAGES CXX)

# PubBus uses C++20 features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(PUBBUS_INSTALL_EXAMPLE "Install PubBus examples" OFF)

include(GNUInstallDirs)

add_subdirectory(examples/Simple)
add_subdirectory(examples/SFML)

add_subdirectory(test)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.hpp")
install(FILES README.md LICENSE.md DESTINATION ${CMAKE_INSTALL_DOCDIR})