set(CH11_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch11)

file(COPY ${CH11_SRC_DIR}/Vec.h DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(11-0 11-0.cpp)
add_executable(11-7 11-7.cpp)
add_executable(11-8 11-8.cpp)

target_include_directories(11-0 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(11-7 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
