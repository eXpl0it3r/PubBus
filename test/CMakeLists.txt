add_executable(Tests "CatchConfig.cpp" "MessageBusTest.cpp" "MessageContainerTest.cpp" "MessageTest.cpp" "SubscriberHandleTest.cpp")

target_include_directories(Tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Tests PRIVATE "${CMAKE_SOURCE_DIR}/include")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(CTest)
include(Catch)

catch_discover_tests(Tests)