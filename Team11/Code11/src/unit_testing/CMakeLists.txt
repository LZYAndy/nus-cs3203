file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/pql_dto/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/PQLParserHelper.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/pql_dto/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/PQLParserHelper.h")
add_executable(unit_testing ${srcs} src/TestAffectsCompute.cpp)

target_link_libraries(unit_testing spa)
