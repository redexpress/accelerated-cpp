set(CH14_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch14)
set(CH13_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch13)
set(CH9_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch9)
set(CH4_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch4)

file(COPY
        ${CH14_SRC_DIR}/Core.h
        ${CH14_SRC_DIR}/Core.cpp
        ${CH14_SRC_DIR}/Handle.h
        ${CH14_SRC_DIR}/Ref_handle.h
        ${CH13_SRC_DIR}/read_hw.h
        ${CH13_SRC_DIR}/read_hw.cpp
        ${CH9_SRC_DIR}/grade.cpp
        ${CH9_SRC_DIR}/grade.h
        ${CH4_SRC_DIR}/median.cpp
        ${CH4_SRC_DIR}/median.h
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(14-0
        14-0.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/Core.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/grade.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/median.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/read_hw.cpp)

target_include_directories(14-0 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})