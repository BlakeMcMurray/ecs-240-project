cmake_minimum_required(VERSION 3.21)
project(ecs_240_project_copy)

set(CMAKE_CXX_STANDARD 20)

add_executable(BasiK src/main.cpp src/scanner.cpp src/program.cpp src/command.cpp src/complexCommand.cpp src/assignment.cpp src/expression.cpp)

target_include_directories(BasiK PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:/Users/noahtarr/opt/anaconda3/envs/ecs240/include/>
)
