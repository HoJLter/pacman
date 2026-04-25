cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

project (cpp-course)

set(CMAKE_PREFIX_PATH "external/")

find_package(SFML REQUIRED COMPONENTS graphics system window audio)

file(GLOB_RECURSE SOURCES
    src/*.cpp
    include/*.h
)

add_executable(app ${SOURCES})

target_include_directories(app PRIVATE include)
target_link_libraries(app PRIVATE sfml-graphics sfml-system sfml-window sfml-audio)

add_custom_command(TARGET app POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/external/SFML/bin
	$<TARGET_FILE_DIR:app>
)


add_custom_command(TARGET app POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:app>/assets"
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_SOURCE_DIR}/assets"
	"$<TARGET_FILE_DIR:app>/assets"
)
