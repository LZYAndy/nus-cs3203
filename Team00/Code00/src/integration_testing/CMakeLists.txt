file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(integration_testing ${srcs} src/TestPQL.cpp src/TestAssignParserPKB.cpp src/TestPrintParserPKB.cpp src/TestReadParserPKB.cpp src/TestCallParserPKB.cpp src/TestIfParserPKB.cpp src/TestWhileParserPKB.cpp)


target_link_libraries(integration_testing spa)
