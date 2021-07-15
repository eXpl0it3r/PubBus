add_executable(Simple "Simple.cpp")

target_include_directories(Simple PRIVATE "${CMAKE_SOURCE_DIR}/include")

if(PUBBUS_INSTALL_EXAMPLE)
    install(TARGETS Simple RUNTIME DESTINATION examples)
endif()