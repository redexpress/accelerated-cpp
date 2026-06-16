set(CH4_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch4)
set(CH9_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch9)

file(COPY ${CH9_SRC_DIR}/Student_info.cpp
        ${CH9_SRC_DIR}/Student_info.h
        ${CH9_SRC_DIR}/grade.cpp
        ${CH9_SRC_DIR}/grade.h
        ${CH4_SRC_DIR}/median.cpp
        ${CH4_SRC_DIR}/median.h
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(9-0
        9-0.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/Student_info.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/grade.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/median.cpp)

add_executable(9-1 9-1.cpp ${CMAKE_CURRENT_BINARY_DIR}/median.cpp)
add_executable(9-2 9-2.cpp ${CMAKE_CURRENT_BINARY_DIR}/median.cpp)

target_include_directories(9-0 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(9-1 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(9-2 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})