add_executable(run_tests test_main.cpp)
target_link_libraries(run_tests PRIVATE maze_router)

add_test(NAME MazeRouterTests COMMAND run_tests)