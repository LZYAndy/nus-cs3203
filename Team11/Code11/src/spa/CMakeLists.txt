file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/pql_dto/*.cpp" "{CMAKE_CURRENT_SOURCE_DIR}/src/Cache.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/pql_dto/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/pql_dto/*.hpp")
add_library(spa ${srcs} ${headers} src/ConverterUtil.cpp src/ConverterUtil.h)

# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
