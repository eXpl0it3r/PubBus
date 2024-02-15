find_package(SFML 2.6 COMPONENTS graphics REQUIRED)

add_executable(SFML "SFML.cpp" "Messages.hpp")

target_include_directories(SFML PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(SFML sfml-graphics)

if(PUBBUS_INSTALL_EXAMPLE)
    install(TARGETS SFML RUNTIME DESTINATION examples)
endif()