file(GLOB_RECURSE SOURCES "*.c")

add_executable(example ${SOURCES})
target_link_libraries(example libnewt)