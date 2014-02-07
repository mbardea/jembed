project(chost)

set(EXE ${PROJECT_NAME})

include_directories(${JNI_INCLUDE_DIRS})
add_executable(${EXE} main.c)
target_link_libraries(${EXE} ${JNI_LIBRARIES})
