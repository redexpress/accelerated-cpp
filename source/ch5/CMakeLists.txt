set(CH4_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch4)

file(COPY ${CH4_SRC_DIR}/Student_info.cpp
        ${CH4_SRC_DIR}/Student_info.h
        ${CH4_SRC_DIR}/median.cpp
        ${CH4_SRC_DIR}/median.h
        ${CH4_SRC_DIR}/grade.h
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ch5_app
        split.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/Student_info.cpp
        grade.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/median.cpp)

target_include_directories(ch5_app PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
