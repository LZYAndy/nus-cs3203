file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/pql_dto/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/pql_dto/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs} src/TestBank.cpp src/TestFollowsBank.cpp src/TestAssignBank.cpp src/TestParentBank.cpp src/TestParentStarBank.cpp src/TestFollowsStarBank.cpp src/TestDesignExtractor.cpp src/TestUsesBank.cpp src/TestModifiesBank.cpp src/TestCheckerUtil.cpp src/TestAssignParser.cpp src/TestPrintParser.cpp src/TestReadParser.cpp)

target_link_libraries(unit_testing spa)