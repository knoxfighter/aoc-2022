cmake_minimum_required(VERSION 3.21)

project(aoc_2022)

set(CMAKE_CXX_STANDARD 23)

find_package(cxxopts REQUIRED)
find_package(CURL REQUIRED)
find_package(magic_enum REQUIRED)

add_executable(aoc_2022 main.cpp FileEntry.cpp FileEntry.h Day9.h Day9.cpp Day11.h Day11.cpp Helper.h Day12.cpp Day12.h)
target_compile_features(aoc_2022 PRIVATE cxx_std_17)

target_link_libraries(aoc_2022
        cxxopts::cxxopts
        CURL::libcurl
        magic_enum::magic_enum
        )

if(WIN32)
target_link_libraries(aoc_2022
        wldap32.lib
        crypt32.lib
        Ws2_32.lib
        )
endif()
