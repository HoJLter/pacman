cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

project (cpp-course)

set(CMAKE_PREFIX_PATH "external/")

find_package(SFML REQUIRED COMPONENTS graphics system window)

add_executable(app 
	"src/main.cpp"
	"src/core/Application.cpp"
	"src/ui/Button.cpp"
	"src/ui/Label.cpp"
	
	"src/scenes/InitialScene.cpp"
	"src/scenes/DotCountInputScene.cpp"
	"src/scenes/DotInputScene.cpp"
	"src/scenes/ResultScene.cpp"
	"include/ui/InputField.h" 
	"src/ui/InputField.cpp" 
	"src/core/SceneManager.cpp"
 "include/core/ISceneSwitcher.h"  "include/utils/Logger.h" 
"src/utils/Logger.cpp" "src/utils/Log.cpp" "include/utils/Log.h"   "src/scenes/TestsScene.cpp" "include/ui/UI.h" "include/algo/Triangulators.h" "include/algo/Geometry.h" "src/algo/Triangulators.cpp" "src/algo/Geometry.cpp")

target_include_directories(app PRIVATE include)
target_link_libraries(app PRIVATE sfml-graphics sfml-system sfml-window)

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
