cmake_minimum_required(VERSION 3.10)
project(Server)

set(CMAKE_C_STANDARD 11)

add_compile_options(-fno-stack-protector)
add_executable(server server.c)
add_executable(client client.c)
