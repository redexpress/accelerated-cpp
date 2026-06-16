set(CH4_SRC_DIR ${CMAKE_SOURCE_DIR}/source/ch4)

file(COPY ${CH4_SRC_DIR}/median.cpp
        ${CH4_SRC_DIR}/median.h
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ch9_app
        gradeapp.cpp
        Student_info.cpp
        grade.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/median.cpp)

target_include_directories(ch9_app PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
