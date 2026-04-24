cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

project (cpp-course)

set(CMAKE_PREFIX_PATH "external/")

find_package(SFML REQUIRED COMPONENTS graphics system window)

add_executable(app "src/app.cpp" "src/utils/Log.cpp" "src/utils/Logger.cpp" "src/core/GameEngine.cpp"     "include/scenes/Scene.h"  "include/Scenes.h" "include/core/ISceneSwitcher.h" "include/core/SceneManager.h" "include/scenes/MenuScene.h" "include/scenes/GameScene.h" "src/core/SceneManager.cpp" "src/ui/Button.cpp" "src/ui/Label.cpp" "include/ui/Button.h" "include/ui/Label.h"  "src/scenes/MenuScene.cpp" "src/scenes/GameScene.cpp")

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
