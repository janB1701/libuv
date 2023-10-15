cmake_minimum_required(VERSION 3.0.0)
project(libuv-project VERSION 0.1.0)

add_executable(network-dissector-final src/network_dissector.c)
add_executable(timer src/timer.c)
add_executable(tcp src/tcp_calculator.c)

target_link_libraries(tcp uv)
target_link_libraries(timer uv)