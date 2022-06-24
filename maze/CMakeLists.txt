add_executable(maze MACOSX_BUNDLE maze.cpp)

target_link_libraries(maze fssimplewindow)
target_link_libraries(maze ysclass)
target_link_libraries(maze ysbitmapfont)
