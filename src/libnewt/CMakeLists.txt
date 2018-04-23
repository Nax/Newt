file(GLOB_RECURSE SOURCES "*.c")

add_library(libnewt SHARED ${SOURCES})
add_library(libnewt-static STATIC ${SOURCES})

set_target_properties(libnewt PROPERTIES OUTPUT_NAME "newt")

if (WIN32)
	set_target_properties(libnewt-static PROPERTIES OUTPUT_NAME "newt-static")
else()
	set_target_properties(libnewt-static PROPERTIES OUTPUT_NAME "newt")
endif()

target_include_directories(libnewt PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(libnewt-static PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_compile_definitions(libnewt PRIVATE "-DNEWT_EXPORT_DLL=1")
target_compile_definitions(libnewt-static PUBLIC "-DNEWT_STATIC=1")