set(CH4_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch4)
set(CH9_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch9)

file(COPY
        ${CH9_SRC_DIR}/grade.cpp
        ${CH9_SRC_DIR}/grade.h
        ${CH4_SRC_DIR}/median.cpp
        ${CH4_SRC_DIR}/median.h
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ch13_app
        coreapp.cpp
        read_hw.cpp
        Core.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/grade.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/median.cpp)

add_executable(ch13_app2
        gradapp.cpp
        read_hw.cpp
        Core.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/grade.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/median.cpp)

add_executable(ch13_app2
        coreapp2.cpp
        read_hw.cpp
        Core.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/grade.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/median.cpp)

target_include_directories(ch13_app PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(ch13_app2 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(ch13_app3 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
