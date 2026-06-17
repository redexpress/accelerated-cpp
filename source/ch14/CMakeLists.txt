set(CH4_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch4)
set(CH9_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch9)
set(CH13_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch13)

file(COPY
        ${CH9_SRC_DIR}/grade.cpp
        ${CH9_SRC_DIR}/grade.h
        ${CH4_SRC_DIR}/median.cpp
        ${CH4_SRC_DIR}/median.h
        ${CH13_SRC_DIR}/read_hw.h
        ${CH13_SRC_DIR}/read_hw.cpp
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ch14_app
        gradeapp.cpp
        Core.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/read_hw.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/grade.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/median.cpp)

add_executable(ch14_app2
        gradeapp2.cpp
        Core.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/read_hw.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/grade.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/median.cpp)

target_include_directories(ch14_app PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(ch14_app2 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
