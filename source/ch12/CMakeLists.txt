set(CH11_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch11)

file(COPY ${CH11_SRC_DIR}/Vec.h DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ch12_app main.cpp)

target_include_directories(ch12_app PRIVATE ${CMAKE_CURRENT_BINARY_DIR})