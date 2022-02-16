cmake_minimum_required(VERSION 3.22.1)

project(GuileTurtleGraphics)

include_directories(/usr/local/include/)

#add_executable(pipe examples/pipe.c)

#add_executable(fork examples/fork.c)
#add_executable(exec_test examples/exec_test.c)

add_executable(call_libguile examples/call_libguile.c)
link_directories(/usr/local/lib/)
target_link_libraries(call_libguile libguile-3.0.1)


#add_executable(turtle turtle.c)





