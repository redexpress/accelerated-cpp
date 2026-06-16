set(CH4_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch4)

file(COPY ${CH4_SRC_DIR}/Student_info.cpp
        ${CH4_SRC_DIR}/Student_info.h
        ${CH4_SRC_DIR}/grade.cpp
        ${CH4_SRC_DIR}/grade.h
        ${CH4_SRC_DIR}/median.cpp
        ${CH4_SRC_DIR}/median.h
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(7-2
        7-2.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/Student_info.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/grade.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/median.cpp)

target_include_directories(7-2 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})