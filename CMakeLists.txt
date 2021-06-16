cmake_minimum_required(VERSION 3.0.0)
project(libuv VERSION 0.1.0)

add_executable (server server.c)
add_executable (client client.c)
target_link_libraries (server uv)
target_link_libraries (client uv)

add_executable (timer timer.c)
target_link_libraries (timer uv)

add_executable(file-monitor file-monitor.c)
target_link_libraries(file-monitor uv)