set(CH4_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch4)
set(CH9_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch9)
set(CH13_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch13)
set(CH14_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch14)
set(CH15_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch15)

file(COPY
        ${CH9_SRC_DIR}/grade.cpp
        ${CH9_SRC_DIR}/grade.h
        ${CH4_SRC_DIR}/median.cpp
        ${CH4_SRC_DIR}/median.h
        ${CH13_SRC_DIR}/read_hw.h
        ${CH13_SRC_DIR}/read_hw.cpp
        ${CH14_SRC_DIR}/Ptr.h
        ${CH14_SRC_DIR}/Handle.h
        ${CH14_SRC_DIR}/Core.h
        ${CH14_SRC_DIR}/Core.cpp
        ${CH15_SRC_DIR}/Pic.h
        ${CH15_SRC_DIR}/Pic.cpp
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ch16_app
        gradeapp.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/Core.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/Pic.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/read_hw.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/grade.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/median.cpp)

target_include_directories(ch16_app PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
