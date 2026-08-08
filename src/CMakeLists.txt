add_library(maze_router Grid.cpp MazeRouter.cpp)
target_include_directories(maze_router PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Create the terminal visualizer executable
add_executable(maze_visualizer visualizer_main.cpp)
target_link_libraries(maze_visualizer PRIVATE maze_router ftxui::screen ftxui::dom ftxui::component)