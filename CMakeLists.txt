cmake_minimum_required(VERSION 3.18)
project(clmixer)

set(CMAKE_CXX_STANDARD 17)

file(GLOB clmixer_SOURCE CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")
file(GLOB clmixer_test_SOURCE CONFIGURE_DEPENDS "src/helper.h" "src/helper.cpp" "tests/*.cpp")

include_directories(src)

find_package(PkgConfig)
find_package(spdlog REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenCL REQUIRED)

pkg_search_module(GTEST REQUIRED gtest_main)

add_executable(clmixer ${clmixer_SOURCE})
add_executable(clmixer_test ${clmixer_test_SOURCE})

target_link_libraries(clmixer
        OpenCL::OpenCL
        spdlog::spdlog
        Threads::Threads)

target_link_libraries(clmixer_test
        spdlog::spdlog
        ${GTEST_LDFLAGS})

include(CTest)
include(GoogleTest)
gtest_discover_tests(clmixer_test XML_OUTPUT_DIR ".")