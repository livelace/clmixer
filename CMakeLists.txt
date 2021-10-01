cmake_minimum_required(VERSION 3.14)
project(clmixer)

set(CMAKE_CXX_STANDARD 17)

find_package(spdlog REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenCL REQUIRED)

file(GLOB clmixer_SRC CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(clmixer ${clmixer_SRC})

target_link_libraries(clmixer
        OpenCL::OpenCL
        spdlog::spdlog
        Threads::Threads)
